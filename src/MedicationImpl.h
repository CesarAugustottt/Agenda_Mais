/**
 * @file MedicationImpl.h
 * @brief Defines the Body and Handle classes for Medication using the Bridge pattern.
 */

#ifndef MEDICATIONIMPL_H
#define MEDICATIONIMPL_H

#include "Medication.h"
#include "handleBody.h" // Replaced Bridge.h with handleBody.h for consistency
#include <string>

/**
 * @class MedicationBody
 * @brief Concrete implementation (Body) of the Medication class.
 * * This class holds the actual data and implements the business logic for the 
 * Medication entity following the Handle/Body (Bridge) idiom.
 */
class MedicationBody : public Body {
protected:
    std::string name;             ///< The name of the medication.
    int quantity;                 ///< The current quantity in stock.
    bool requiresPrescription;    ///< Flag indicating if a prescription is needed.

public:
    MedicationBody();
    
    /**
     * @brief Destructor.
     */
    virtual ~MedicationBody();

    std::string getName() const;
    int getQuantity() const;
    bool getRequiresPrescription() const;

    void setName(const std::string& name);
    void setQuantity(int quantity);
    void setRequiresPrescription(bool requires);
    
    bool decreaseStock(int amount);
};

/**
 * @class MedicationHandle
 * @brief The Handle class for Medication.
 * * This class acts as a proxy/wrapper for MedicationBody, managing its lifecycle 
 * (reference counting) and delegating method calls to the underlying implementation.
 */
class MedicationHandle : public Medication, public Handle<MedicationBody> {
protected:
    /**
     * @brief Constructor for MedicationHandle.
     * @param name The name of the medication.
     * @param quantity Initial quantity in stock.
     * @param requiresPrescription True if it requires a prescription.
     */
    MedicationHandle(const std::string& name, int quantity, bool requiresPrescription);

    MedicationHandle();
public:
    
    /**
     * @brief Destructor.
     */
    virtual ~MedicationHandle();

    std::string getName() const override;
    int getQuantity() const override;
    bool requiresPrescription() const override;

    void setName(const std::string& name) override;
    void setQuantity(int quantity) override;
    void setRequiresPrescription(bool requires) override;
    
    bool decreaseStock(int amount) override;
};

#endif
