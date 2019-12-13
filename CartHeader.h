/**
 * \file CartHeader.h
 * \author Sean C.
 * \version 1.0
 * Contains functions and classes relating to the cartridge header.
 */

#ifndef CARTHEADER_H_INCLUDED
#define CARTHEADER_H_INCLUDED
#include "BitFunctions.h"
#include <string>
#include <iostream>

/**
 *  \namespace HeaderLocations
 *  Contains constants that define the locations in the header for important information.
 */


namespace HeaderLocations
{
    extern const uint32_t EntryPoint; /**< The entry point of the gameboy program*/
    extern const uint32_t Logo;       /**< The position of the logo in the header*/
    extern const uint32_t Title;      /**< The location of the title in the header*/
    extern const uint32_t ManufacturerCode; /**< The location of the manufacturer code*/
    extern const uint32_t CgbFlag;          /**< The location of the CgbFlag*/
    extern const uint32_t NewLicenseCode;   /**< The location of the licensing code*/
    extern const uint32_t SgbFlag;          /**< The location of the sgb flag*/
    extern const uint32_t CartridgeTypePos; /**< The location of the cartridge type number*/
    extern const uint32_t RomSizePos;       /**< The location of the number that specifies the RomSize*/
    extern const uint32_t RamSizePos;       /**< The location of the number that specifies the RamSize*/
    extern const uint32_t DestinationCode;  /**< Specifies the region*/
    extern const uint32_t OldLicenseCode;   /**< Specifies the old licensing code*/
    extern const uint32_t VersionNumber;    /**< The version number of the cartridge*/
    extern const uint32_t HeaderChecksum;   /**< A checksum of the cartridge header*/
    extern const uint32_t GlobalChecksum;   /**< A checksum of the cartridge*/
}

extern const char* CartridgeTypeTexts[];

/**
 *  \enum CartridgeType
 *  An enumerator that specifies the type of cartridge that the cartridge is.
 */
enum class CartridgeType
{
    ROMOnly=0,
    MBC1,
    MBC2,
    MBC3,
    MBC4,
    MBC5,
    Unknown,
};

extern const uint32_t RomSizes[]; /**<A list of the rom sizes in order of the RomSize enumerators*/
extern const char* RomSizeTexts[];/**<A list of rom readable text in order of the romsize enumerator*/

/**
 * enum RomSize
 * Values to represent the different rom sizes that the cartridge can be.
 */
enum class ROMSize
{
    KB32=0,
    KB64,
    KB128,
    KB256,
    KB512,
    MB1,
    MB2,
    MB4,
    MB1p1,
    MB1p2,
    MB1p5,
};

/**
 * enum RAMSize
 * Values to represent the different possible internal cartridge ram size.
 */
enum class RAMSize
{
    None=5,
    KB2=0,
    KB8=1,
    KB32=2,
    KB128=3,
    KB64=4,
};

/**
 * enum Destination
 * An enumerator to specify values to represent the different regions
 */
enum class Destination
{
    Japanese,
    NonJapanese,
};

/**
 * \fn CartridgeType GetType(uint8_t type)
 * \param type The byte to represent the cartridge type in the header.
 * \return The value that represents the cartridge type.
 * Gets the cartridge type enumerator from the cartridge header byte.
 */
CartridgeType GetType(uint8_t type);

/**
 * \fn std::string ToString(CartridgeType type)
 * \param type The enumeration representation of the cartridge type.
 * \return The readable version of the cartridge type.
 * Gets a readable string specifying the cartridge type.
 */
std::string ToString(CartridgeType type);

/**
 * \fn ROMSize GetRomSizeCode(uint8_t Size)
 * \param Size The byte representing the rom size.
 * \return An enumeration equivilent of the rom size code.
 * Gets an enumeration representing the rom size from the header byte.
 */
ROMSize GetRomSizeCode(uint8_t Size);


/**
 * \fn size_t GetRomSize(ROMSize size)
 * \param size The enumerator representation of the rom size.
 * \return The size of the ROM in bytes.
 * Gets the rom size in bytes from the rom size enumerator.
 */
size_t GetRomSize(ROMSize size);

/**
 * \fn std::string ToString(ROMSize size)
 * \param size The enumerator representing the rom size.
 * \return A readable string representation of the rom size.
 * Gets a readable representation of the rom size from the enumeration.
 */
std::string ToString(ROMSize size);


/**
 * \fn RAMSize GetRamSizeCode(uint8_t SizeCode)
 * \param SizeCode the byte representing the ram size in the header.
 * \return The enumeration equivilent of the ram size code.
 * Gets an enumerator equivilent of the ram size code.
 */
RAMSize GetRamSizeCode(uint8_t SizeCode);


extern const uint32_t RamSizes[];

/**
 * \fn uint32_t GetRamSize(RAMSize size)
 * \param RAMSize the enumerator equivilent of the ram size.
 * \return The ram size in bytes.
 * Gets the size of the ram in bytes from the enumerator.
 */
uint32_t GetRamSize(RAMSize size);

/**
 * \fn std::string ToString(RAMSize size)
 * \param size The enumerator equivilent of the ram size.
 * \return A human readable equivelent of the ram size.
 * Gets human readable text representation of the ram size.
 */
std::string ToString(RAMSize size);

/**
 * \fn Destination GetDestination(uint8_t destination)
 * \param destination The byte in the header that specifies the region.
 * \return Gets an enumerator to represent the region the rom is meant for.
 * Gets an enumerator of the region from the byte that represents the destination in the header.
 */
Destination GetDestination(uint8_t destination);


/**
 * \fn std::string ToString(Destination destination)
 * \param destination The enumerator representing the region.
 * \return A human readable text of the region.
 * Gets human readable text representing the intended region for the cart.
 */
std::string ToString(Destination destination);

/**
 * \fn std::string GetTitle(uint8_t* rom)
 * \param rom The cart rom.
 * \return The title of the rom.
 * Gets the title of the rom that is loaded.
 */
std::string GetTitle(uint8_t* rom);

/**
 * \class CartHeader
 * A class to represent the gameboy cart header.
 */
class CartHeader
{
public:

/**
 * \fn void Create(uint8_t* RomBytes)
 * \param RomBytes the rom cart data.
 * Loads the cart header into the class from the cartridge data.
 */
    void Create(uint8_t* RomBytes);

/**
 * void Dump(std::ostream& out)
 * \param out The stream to dump to.
 * Dumps human readable cartridge data to the stream specified.
 */
    void Dump(std::ostream& out);

    CartridgeType Type; /**<The cartridge type enumerator*/
    Destination Dest;   /**<The region of the rom*/
    ROMSize ROM;        /**<The size of the rom*/
    RAMSize RAM;        /**<The size of the ram*/

    bool CBG;           /**<Color game boy flag*/
    bool SGB;           /**<The super game boy flag*/

    std::string Title;  /**<The title of the rom*/
    uint8_t Version;    /**<The version byte of the cartridge*/
private:
};

#endif // CARTHEADER_H_INCLUDED
