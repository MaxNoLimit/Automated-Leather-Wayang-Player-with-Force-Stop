#ifndef A4988_NEMA_H
#define A4988_NEMA_H

#define PERIOD_NEMA 3 // 3 ms

#include "mainheader.hpp"

class HorizontalController{
    private: 
    int step_value;


    public:
    // void cw_step(int nema_num);
    // void ccw_step(int nema_num);

    void step_for_n_dir(int nema_num, int step_value, String dir);
    // void step_for_what_distance(int nema_num, int distance);
};

#endif // A4988_NEMA_H