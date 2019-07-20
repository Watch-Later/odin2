#pragma once

#include "../../GlobalIncludes.h"
#include "Filter.h"
#include "VAOnePoleFilter.h"

class LadderFilter : public Filter {
public:
  enum class FILTERTYPE {
    LP4 = 0,
    LP2 = 1,
    BP4 = 2,
    BP2 = 3,
    HP4 = 4,
    HP2 = 5
    // todo bandstop?
  };

  LadderFilter(void);
  ~LadderFilter(void);

  // -- Filter Overrides --
  virtual void reset() override;
  virtual void setResControl(double p_res) override;

  inline virtual void update() {

    m_k_modded = m_k + 4 * (*m_res_mod);
    m_k_modded = m_k_modded > 3.88 ? 3.88 : m_k_modded;
    m_k_modded = m_k_modded < 0 ? 0 : m_k_modded;

    // do any modulation first
    Filter::update();

    // prewarp for BZT
    double wd = 2 * M_PI * m_freq_modded;
    double T = 1 / m_samplerate;
    double wa = (2 / T) * tan(wd * T / 2);
    double g = wa * T / 2;

    // G - the feedforward coeff in the VA One Pole
    //     same for LPF, HPF
    double G = g / (1.0 + g);

    // set alphas
    m_LPF1.m_alpha = G;
    m_LPF2.m_alpha = G;
    m_LPF3.m_alpha = G;
    m_LPF4.m_alpha = G;

    // set betas
    m_LPF1.m_beta = G * G * G / (1.0 + g);
    m_LPF2.m_beta = G * G / (1.0 + g);
    m_LPF3.m_beta = G / (1.0 + g);
    m_LPF4.m_beta = 1.0 / (1.0 + g);

    m_gamma = G * G * G * G; // G^4

    m_alpha_0 = 1.0 / (1.0 + m_k_modded * m_gamma);

    // Oberheim variation
    switch (m_filter_type) {
    case FILTERTYPE::LP4:
      m_a = 0.0;
      m_b = 0.0;
      m_c = 0.0;
      m_d = 0.0;
      m_e = 1.0;
      break;

    case FILTERTYPE::LP2:
      m_a = 0.0;
      m_b = 0.0;
      m_c = 1.0;
      m_d = 0.0;
      m_e = 0.0;
      break;

    case FILTERTYPE::BP4:
      m_a = 0.0;
      m_b = 0.0;
      m_c = 4.0;
      m_d = -8.0;
      m_e = 4.0;
      break;

    case FILTERTYPE::BP2:
      m_a = 0.0;
      m_b = 2.0;
      m_c = -2.0;
      m_d = 0.0;
      m_e = 0.0;
      break;

    case FILTERTYPE::HP4:
      m_a = 1.0;
      m_b = -4.0;
      m_c = 6.0;
      m_d = -4.0;
      m_e = 1.0;
      break;

    case FILTERTYPE::HP2:
      m_a = 1.0;
      m_b = -2.0;
      m_c = 1.0;
      m_d = 0.0;
      m_e = 0.0;
      break;

    default: // LP4
      m_a = 0.0;
      m_b = 0.0;
      m_c = 0.0;
      m_d = 0.0;
      m_e = 1.0;
      break;
    }
  }

  inline void enablePassBandCompensation() { m_aux_control = 1.f; }

  inline virtual double doFilter(double xn) {

    double dSigma = m_LPF1.getFeedbackOutput() + m_LPF2.getFeedbackOutput() +
                    m_LPF3.getFeedbackOutput() + m_LPF4.getFeedbackOutput();

    // --- for passband gain compensation
    //     you can connect this to a GUI control
    //     and let user choose instead
    // todo wut?
    xn *= 1.0 + m_aux_control * m_k_modded;

    // calculate input to first filter
    double dU = (xn - m_k_modded * dSigma) * m_alpha_0;

    // --- cascade of 4 filters
    double dLP1 = m_LPF1.doFilter(dU);
    double dLP2 = m_LPF2.doFilter(dLP1);
    double dLP3 = m_LPF3.doFilter(dLP2);
    double dLP4 = m_LPF4.doFilter(dLP3);

    // --- Oberheim variations
    double output = m_a * dU + m_b * dLP1 + m_c * dLP2 + m_d * dLP3 + m_e * dLP4;

	  applyOverdrive(output);

    float vol_mod_factor =
        (*m_vol_mod) > 0 ? 1.f + 4 * (*m_vol_mod) : (1.f + *m_vol_mod);

    return output * vol_mod_factor;
  }

  

  inline void setFilterType(int p_filtertype) {
    m_filter_type = (FILTERTYPE)p_filtertype;
  }

  VAOnePoleFilter m_LPF1;
  VAOnePoleFilter m_LPF2;
  VAOnePoleFilter m_LPF3;
  VAOnePoleFilter m_LPF4;

  FILTERTYPE m_filter_type = FILTERTYPE::LP4;

  // variables
  double m_k; // K, set with Q
  double m_k_modded;
  double m_gamma;   // see block diagram
  double m_alpha_0; // see block diagram

  // Oberheim Xpander variations
  double m_a;
  double m_b;
  double m_c;
  double m_d;
  double m_e;
};
