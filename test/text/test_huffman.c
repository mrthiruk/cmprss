#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h>

#include "cmprss_common.h"
#include "huffman.h"

int 
main(void)
{
	char *str = "There they go, Packing stadiums as Shady spits his flow!"
				"Nuts they go, Macadamian! They throw a ballistic wow!";
	cmprss_huffman_encode(str, strlen(str), NULL, NULL);
}
