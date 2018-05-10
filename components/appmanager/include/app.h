#ifndef APP_H
#define APP_H 
#include <stdint.h>

#define APP_NAME_BYTES			30
#define COMPANY_NAME_BYTES 		30

typedef struct {
	uint8_t release;
	uint8_t func_added;
	uint8_t bug_fixed;
}appversion_t;

typedef struct {
	appversion_t app_version;			 //!< version of the app
 	// uint16_t size;                    //!< size of the app binary, including this metadata but not the reloc table
 	// uint32_t offset;                  //!< The entry point of this executable
 	// uint32_t crc;                     //!< CRC of the app data only, ie, not including this struct or the reloc table at the end
 	char name[APP_NAME_BYTES];        	 //!< Name to display on the menu
 	char company[COMPANY_NAME_BYTES]; 	 //!< Name of the maker of this app
 	// uint32_t icon_resource_id;        //!< Resource ID within this app's bank to use as a 32x32 icon
 	// uint32_t sym_table_addr;          //!< The system will poke the sdk's symbol table address into this field on load
 	// uint32_t flags;                   //!< Bitwise OR of PebbleAppFlags
 	// uint32_t reloc_list_start;        //!< The offset of the address relocation list
 	// uint32_t num_reloc_entries;       //!< The number of entries in the address relocation list

    void (*on_init)(void);
    void (*on_change)(void);
    void (*on_close)(void);
    void (*bluetooth)(void);
    void (*gyro)(void);
    void (*pulse_oximeter)(void);
    void (*heart_rate)(void);
} app_t;

#endif