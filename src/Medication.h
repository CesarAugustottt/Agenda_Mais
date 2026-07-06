/**
 * @file Medication.h
 * @brief Defines the abstract interface for the Medication entity.
 * * This file contains the declaration of the Medication class, which acts as 
 * the interface for all medication-related operations in the system.
 */

#ifndef MEDICATION_H
#define MEDICATION_H

#include <string>

/**
 * @class Medication
 * @brief Abstract base class representing a medication.
 * * Provides an interface to access and modify medication details such as 
 * name, quantity in stock, and whether it requires a prescription.
 */
class Medication {
public:
    /**
     * @brief Virtual destructor.
     */
    virtual ~Medication() {}
    
    /**
     * @brief Gets the name of the medication.
     * @return A std::string containing the medication's name.
     */
    virtual std::string getName() const = 0;

    /**
     * @brief Gets the current quantity of the medication in stock.
     * @return An integer representing the stock quantity.
     */
    virtual int getQuantity() const = 0;

    /**
     * @brief Checks if the medication requires a medical prescription.
     * @return True if a prescription is required, false otherwise.
     */
    virtual bool requiresPrescription() const = 0;
    
    /**
     * @brief Sets the name of the medication.
     * @param name The new name to be assigned to the medication.
     */
    virtual void setName(const std::string& name) = 0;

    /**
     * @brief Sets the quantity of the medication in stock.
     * @param quantity The new stock quantity.
     */
    virtual void setQuantity(int quantity) = 0;

    /**
     * @brief Sets whether the medication requires a prescription.
     * @param requires true if it requires a prescription, false otherwise.
     */
    virtual void setRequiresPrescription(bool requires) = 0;
    
    /**
     * @brief Decreases the medication stock by a given amount.
     * * This method is used when a reservation is made, reducing the available stock.
     * * @param amount The amount to subtract from the current stock.
     * @return True if the stock was successfully decreased (sufficient stock), false otherwise.
     */
    virtual bool decreaseStock(int amount) = 0;
};

#endif
