#pragma once

#include "Page.h"
#include "Measurement.h"
#include "helpers.h"

class CurrentPage : public Page
{
private:
    // Display texts for live values
    DisplayText dt_1;
    DisplayText dt_2;
    DisplayText dt_3;

    uint32_t upre_adc;
    uint32_t u_adc;

public:
    virtual void initialize(Graphics *) override;

    // repaint the whole page (clear and pait evrything)
    virtual void repaint(Graphics *);

    // this page only shows the raw current values and calculations
    void set_u_adc_raw(uint32_t adcval);
    void set_upre_adc_raw(uint32_t adcval);

    // Update loop
    virtual void loop(uint64_t loopCount, Graphics *disp);

protected:
    void updateCurrent();
};