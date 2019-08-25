#pragma once

#include "Page.h"

class AnalogPage : public Page
{
    DisplayText dt_q;
    DisplayText dt_p;
    DisplayText dt_ps;

    uint8_t dig_bef_com;

public:
    // Initialization
    virtual void initialize(Graphics *);

    // repaint the whole page (clear and pait evrything)
    virtual void repaint(Graphics *);

    // Setter for live values
    virtual void set_q_set(const rkp::PhysicalValue&);
    virtual void set_q_is(const rkp::PhysicalValue&);
    virtual void set_p_set(const rkp::PhysicalValue&);
    virtual void set_p_is(const rkp::PhysicalValue&);
    virtual void set_ps_pre_set(const rkp::PhysicalValue&);
    virtual void set_ps_set(const rkp::PhysicalValue&);

    void setDigBefCom(uint8_t);
    uint8_t getDigBefCom();

    // Update loop
    virtual void loop(uint64_t loopCount, Graphics *disp);
};