/**
 * \file Cart.h
 * \author Sean C
 * \version 1.0
 * Defines a base class for all cartridge types.
 */


#ifndef CART_H_INCLUDED
#define CART_H_INCLUDED
#include "CartHeader.h"
#include <fstream>


/**
 * \class Cart
 * A base virtual class for all cartridge types.
 */

class Cart
{
public:

/**
 * \fn ~Cart()
 * Destructor, cleaning up any memory used by the cartridge.
 */
    virtual ~Cart();

/**
 * \fn virtual uint8_t Read(uint16_t Address)=0
 * \param Address the address to read from the cartridge (Absolute)
 * \return The byte read from memory.
 * Function to be overridden with a function to read from cartridge memory.
 */
    virtual uint8_t Read(uint16_t Address)=0;

/**
 * \fn virtual void Write(uint16_t Address, uint8_t Value)=0
 * \param Address the address to write at (Absolute value)
 * \param Value the value to write
 * Function to be overridden with a function to write to the cart.
 */
    virtual void Write(uint16_t, uint8_t)=0;

/**
 * \fn virtual uint8_t* GetPointer(uint16_t Address)=0
 * \param Address the address to get the pointer of
 * \return A pointer to the memory of address.
 * Gets a pointer to the cartridge memory of address.
 */
    virtual uint8_t* GetPointer(uint16_t)=0;

/**
 * \fn virtual bool SaveState(std::ofstream& out)
 * \param out The stream to save to.
 * \return True on success, false on failure.
 * Saves the state of the cartridge to out stream.
 */
    virtual bool SaveState(std::ofstream& out);

/**
 * \fn virtual bool LoadState(std::ifstream& in)
 * \param in The stream to load from
 * \return True on success, false on failure.
 * Loads the state of the cartridge from the in stream.
 */
    virtual bool LoadState(std::ifstream& in);

    static uint8_t CartRead(uint16_t Address, void* P);
    static void CartWrite(uint16_t Address, uint8_t Value, void* P);

/**
 * \fn bool ContainsSRAM(void)
 * \return True if the cart has SRAM, false otherwise.
 * Returns whether or not the cartridge contains SRAM.
 */
    bool ContainsSRAM(void);

/**
 * \fn virtual void SaveRam(std::ofstream& out)
 * \param out The stream to save the ram to.
 * Saves the internal cart ram to the out stream.
 */
    virtual void SaveRam(std::ofstream& out);

/**
 * \fn virtual void LoadRam(std::ifstream& in)
 * \param in The stream to load the ram from.
 * Loads the internal cart ram from the in stream.
 */
    virtual void LoadRam(std::ifstream& in);

    uint8_t* Rom;   /**<Pointer to the rom data*/
    size_t RomSize; /**<Size of the rom data*/
    uint8_t* Ram;   /**<Pointer to the cart ram data*/
    size_t RamSize; /**<Size of the cart ram data*/

    CartHeader Head;/**<Header data of the cartridge*/
};


#include "MBC.h"
#include "RomOnly.h"

#endif // CART_H_INCLUDED
