/*
** Odin 2 Synthesizer Plugin
** Copyright (C) 2020 TheWaveWarden
**
** Odin 2 is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Odin 2 is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
*/

#include <cmath>
#include <fstream>
#include "../../JUCE/modules/juce_dsp/maths/juce_FastMathApproximations.h"

int main()
{
    std::ofstream exp;
    exp.open("exp.exp");
    exp << "x;std::exp;juce::exp;difference;quotient\n";
    for (float x = -6; x < 4; x += 0.05)
    {
        exp << x << ";" << std::exp(x) << ";" << juce::dsp::FastMathApproximations::exp(x) << ";" << std::exp(x) - juce::dsp::FastMathApproximations::exp(x) << ";" << juce::dsp::FastMathApproximations::exp(x) / std::exp(x) << "\n";
    }
    exp.close();

    std::ofstream pitchshift;
    pitchshift.open("pitchshift.csv");
    pitchshift << "semitone;error_in_cents\n";
    double factor = std::log(2.) / 12.;
    for (int st = -48; st <= 48; ++st){
        //pitchshift << st << ";" << st * factor << "\n";
         double stdexp = std::exp(st *factor);
         double juceexp = juce::dsp::FastMathApproximations::exp(st * factor);

         double cents = std::log(juceexp /stdexp) / factor * 100;
         pitchshift << st << ";" << cents << "\n";
    }

    return 0;
}