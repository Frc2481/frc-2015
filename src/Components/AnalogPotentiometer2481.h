/*
 * AnalogPotentiometer2481.h
 *
 *  Created on: Feb 11, 2015
 *      Author: Team2481
 */

#ifndef SRC_COMPONENTS_ANALOGPOTENTIOMETER2481_H_
#define SRC_COMPONENTS_ANALOGPOTENTIOMETER2481_H_

#include "AnalogInput.h"
#include "interfaces/Potentiometer.h"
#include "LiveWindow/LiveWindowSendable.h"

/**
 * Class for reading analog potentiometers. Analog potentiometers read
 * in an analog voltage that corresponds to a position. The position is
 * in whichever units you choose, by way of the scaling and offset
 * constants passed to the constructor.
 *
 * @author Alex Henning
 * @author Colby Skeggs (rail voltage)
 */
class AnalogPotentiometer2481 : public Potentiometer, public LiveWindowSendable {
public:
    /**
     * AnalogPotentiometer2481 constructor.
     *
     * Use the fullRange and offset values so that the output produces
     * meaningful values. I.E: you have a 270 degree potentiometer and
     * you want the output to be degrees with the halfway point as 0
     * degrees. The fullRange value is 270.0(degrees) and the offset is
     * -135.0 since the halfway point after scaling is 135 degrees.
     *
     * This will calculate the result from the fullRange times the
     * fraction of the supply voltage, plus the offset.
     *
     * @param channel The analog channel this potentiometer is plugged into.
     * @param fullRange The scaling to multiply the voltage by to get a meaningful unit.
     * @param offset The offset to add to the scaled value for controlling the zero value
     */
    explicit AnalogPotentiometer2481(int channel, double fullRange = 1.0, double offset = 0.0);

    explicit AnalogPotentiometer2481(AnalogInput *input, double fullRange = 1.0, double offset = 0.0);

    explicit AnalogPotentiometer2481(AnalogInput &input, double fullRange = 1.0, double offset = 0.0);

    virtual ~AnalogPotentiometer2481();

    /**
     * Get the current reading of the potentiomer.
     *
     * @return The current position of the potentiometer.
     */
    virtual double Get();


    /**
     * Implement the PIDSource interface.
     *
     * @return The current reading.
     */
    virtual double PIDGet();


    /*
     * Live Window code, only does anything if live window is activated.
     */
    virtual std::string GetSmartDashboardType();
    virtual void InitTable(ITable *subtable);
    virtual void UpdateTable();
    virtual ITable* GetTable();

    /**
     * AnalogPotentiometer2481s don't have to do anything special when entering the LiveWindow.
     */
    virtual void StartLiveWindowMode() {}

    /**
     * AnalogPotentiometer2481s don't have to do anything special when exiting the LiveWindow.
     */
    virtual void StopLiveWindowMode() {}

    void SetOffset(double offset);

private:
    double m_fullRange, m_offset;
    AnalogInput* m_analog_input;
    ITable* m_table;
    bool m_init_analog_input;

    /**
     * Common initialization code called by all constructors.
     */
    void initPot(AnalogInput *input, double fullRange, double offset);
};

#endif /* SRC_COMPONENTS_ANALOGPOTENTIOMETER2481_H_ */
