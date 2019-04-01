#include "WavetableContainer.h"
#include <cmath>
#include <iostream>
#include <fstream>

WavetableContainer::WavetableContainer(){
#include "WavetableCoefficients.h"
}

WavetableContainer::~WavetableContainer()
{
    if (m_wavetables_created)
    {
        destroyWavetables();
    }
}

void WavetableContainer::createWavetables(float p_sample_rate)
{

    // //loop over all wavetables
    for (int index_wavetable = 0; index_wavetable < NUMBER_OF_WAVETABLES; ++index_wavetable)
    {

        // this flags hackishly if a waveform only uses sine components
        bool sine_only = m_fourrier_coeffs[index_wavetable][0][0] > 0.5f ? true : false;

        double seed_freq = 27.5; //A0
        float max = 0.f;

        //loop over subtables
        for (int index_sub_table = 0; index_sub_table < SUBTABLES_PER_WAVETABLE; ++index_sub_table)
        {

            //allocate memory for actual tables
            float *next_table = new float[WAVETABLE_LENGTH];
            memset(next_table, 0, WAVETABLE_LENGTH * sizeof(float));

            //how many harmonics are needed for this subtable
            int number_of_harmonics = (int)((p_sample_rate * 0.5f / seed_freq) - 1);

            //don't allow more than 800 harmonics (for big Samplerates this might happen)
            number_of_harmonics = number_of_harmonics > 801 ? 801 : number_of_harmonics;

            for (int index_harmonics = 1; index_harmonics < number_of_harmonics; ++index_harmonics)
            {
                for (int index_position = 0; index_position < WAVETABLE_LENGTH; ++index_position)
                {

                    //fill table with //sine harmonics
                    next_table[index_position] += m_fourrier_coeffs[index_wavetable][0][index_harmonics] * sin(2.f * PI * index_position * index_harmonics / (float)WAVETABLE_LENGTH) * m_fourrier_coeffs[index_wavetable][1][0]; //last term is normalization
                    if (!sine_only)
                    {
                        //cosine
                        next_table[index_position] += m_fourrier_coeffs[index_wavetable][1][index_harmonics] * cos(2.f * PI * index_position * index_harmonics / (float)WAVETABLE_LENGTH) * m_fourrier_coeffs[index_wavetable][1][0]; //last term is normalization
                    }
                }
            }

            // for(int index_position = 0; index_position < WAVETABLE_LENGTH; ++index_position){
            //     if(fabs(next_table[index_position]) > max){
            //         max = fabs(next_table[index_position]);
            //     }
            // }

            //assign array to corresponding pointer
            m_wavetable_pointers[index_wavetable][index_sub_table] = next_table;

            //increment seed frequency by minor third = 2^(3/12)
            seed_freq *= 1.1892071150;
        }
        m_name_index_map.insert(std::pair<std::string, int>(m_wavetable_names_1D[index_wavetable], index_wavetable));
    }
    m_wavetables_created = true;
}

void WavetableContainer::createChipdrawTable(int p_table_nr, float p_chipdraw_values[CHIPDRAW_LENGTH], float p_sample_rate)
{

    //first generate the fourrier coefficients
    float chipdraw_coefficients[SIN_AND_COS][NUMBER_OF_HARMONICS];

    float step_width = 2 * PI / CHIPDRAW_LENGTH;

    for (int harmonic = 1; harmonic < NUMBER_OF_HARMONICS; ++harmonic)
    {

        float coeff_sine = 0.f;
        float coeff_cosine = 0.f;

        for (int segment = 0; segment < CHIPDRAW_LENGTH; ++segment)
        {
            coeff_sine += const_segment_one_overtone_sine(segment * step_width, (segment + 1) * step_width, p_chipdraw_values[segment], harmonic);
            coeff_cosine += const_segment_one_overtone_cosine(segment * step_width, (segment + 1) * step_width, p_chipdraw_values[segment], harmonic);
        }
        chipdraw_coefficients[0][harmonic] = coeff_sine;
        chipdraw_coefficients[1][harmonic] = coeff_cosine;
    }

    //now create the wavetable from the fourrier coefficients
    double seed_freq = 27.5; //A0
    float max = 0.f;

    //delete old table
    memset(m_chipdraw_tables[p_table_nr], 0, SUBTABLES_PER_WAVETABLE * WAVETABLE_LENGTH * sizeof(float));

    //loop over subtables
    for (int index_sub_table = 0; index_sub_table < SUBTABLES_PER_WAVETABLE; ++index_sub_table)
    {

        //how many harmonics are needed for this subtable
        int number_of_harmonics = (int)((p_sample_rate * 0.5f / seed_freq) - 1);

        //don't allow more than 800 harmonics (for big Samplerates this might happen)
        number_of_harmonics = number_of_harmonics > 801 ? 801 : number_of_harmonics;

        for (int index_position = 0; index_position < WAVETABLE_LENGTH; ++index_position)
        {
            for (int index_harmonics = 1; index_harmonics < number_of_harmonics; ++index_harmonics)
            {

                //fill table with
                //sine harmonics
                m_chipdraw_tables[p_table_nr][index_sub_table][index_position] += chipdraw_coefficients[0][index_harmonics] * sin(2.f * PI * index_position * index_harmonics / (float)WAVETABLE_LENGTH);
                //cosine
                m_chipdraw_tables[p_table_nr][index_sub_table][index_position] += chipdraw_coefficients[1][index_harmonics] * cos(2.f * PI * index_position * index_harmonics / (float)WAVETABLE_LENGTH);
            }
            //find max among all tables
            if (fabs(m_chipdraw_tables[p_table_nr][index_sub_table][index_position]) > max)
            {
                max = fabs(m_chipdraw_tables[p_table_nr][index_sub_table][index_position]);
            }
        }
        //increment seed frequency by minor third = 2^(3/12)
        seed_freq *= 1.1892071150;

        //set pointers
        m_chipdraw_pointers[p_table_nr][index_sub_table] = m_chipdraw_tables[p_table_nr][index_sub_table];
    }

    //do another round to scale the table
    //acoid division by 0
    if(max > 1e-5){
        max = 1.f / max; //for faster computation
    }
    for (int index_sub_table = 0; index_sub_table < SUBTABLES_PER_WAVETABLE; ++index_sub_table){
        for (int index_position = 0; index_position < WAVETABLE_LENGTH; ++index_position){
            m_chipdraw_tables[p_table_nr][index_sub_table][index_position] *= max;
        }
    }

}



float WavetableContainer::const_segment_one_overtone_sine(float p_start, float p_end, float p_height, int p_harmonic)
{
    return p_height / (float)p_harmonic * (cos(p_start * (float)p_harmonic) - cos(p_end * (float)p_harmonic));
}

float WavetableContainer::const_segment_one_overtone_cosine(float p_start, float p_end, float p_height, int p_harmonic)
{
    return p_height / (float)p_harmonic * (sin(p_end * (float)p_harmonic) - sin(p_start * (float)p_harmonic));
}

void WavetableContainer::destroyWavetables()
{
    //delete allocated memory for wavetables
    for (int index_wavetable = 0; index_wavetable < NUMBER_OF_WAVETABLES; ++index_wavetable)
    {
        for (int index_sub_table = 0; index_sub_table < SUBTABLES_PER_WAVETABLE; ++index_sub_table)
        {
            delete[] m_wavetable_pointers[index_wavetable][index_sub_table];
            m_wavetable_pointers[index_wavetable][index_sub_table] = nullptr;
        }
    }
    m_wavetables_created = false;
}

float** WavetableContainer::getChipDrawPointer(int p_chipdraw_index){
    return m_chipdraw_pointers[p_chipdraw_index];
}

float **WavetableContainer::getWavetablePointers(int p_wavetable)
{
    return m_wavetable_pointers[p_wavetable];
}

float **WavetableContainer::getWavetablePointers(std::string p_name)
{
    // for(int wt = 0; wt < NUMBER_OF_WAVETABLES; ++wt){
    //     if(p_name == m_wavetable_names_1D[wt]){
    //         return m_wavetable_pointers[wt];
    //     }
    // }

    auto it = m_name_index_map.find(p_name);
    if (it != m_name_index_map.end())
    {
        return m_wavetable_pointers[it->second];
    }

    return m_wavetable_pointers[0]; //return sine if no wt found
}

void WavetableContainer::changeSampleRate(float p_sample_rate)
{
    if (m_wavetables_created)
    {
        destroyWavetables();
    }
    createWavetables(p_sample_rate);
}

void WavetableContainer::writeScaleFactorsToFile()
{
    std::ofstream file;
    file.open("E:\\odin\\scaleFactors.h");

    for (int wt = 0; wt < NUMBER_OF_WAVETABLES; ++wt)
    {
        float max = 0.f;

        for (int sub = 0; sub < SUBTABLES_PER_WAVETABLE; ++sub)
        {
            float *next_table = m_wavetable_pointers[wt][sub];
            for (int pos = 0; pos < WAVETABLE_LENGTH; ++pos)
            {
                if (fabs(next_table[pos]) > max)
                {
                    max = fabs(next_table[pos]);
                }
            }
        }

        file << "m_fourrier_coeffs[WT_NR][1][0] = " << 1.f / max * 0.99f * m_fourrier_coeffs[wt][1][0] << "; //" << m_wavetable_names_1D[wt] << " scalar\n";
        file << "max was " << max << "\n";
    }

    file.close();
}