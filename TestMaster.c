#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions      */
#include <errno.h>   /* ERROR Number Definitions           */
#include <sys/ioctl.h>
#include <unistd.h>
#include "modbus.h"

int main()
{
    uint8_t req[MODBUS_TCP_MAX_ADU_LENGTH];// request buffer
    int len;// length of the request/response

    //Create a new RTU context with proper serial parameters (in this example,
    //device name /dev/ttyS0, baud rate 9600, no parity bit, 8 data bits, 1 stop bit)
    //modbus_t *ctx = modbus_new_rtu("/dev/pts/3", 9600, 'N', 8, 1);
    modbus_t *ctx = modbus_new_tcp("127.0.0.1",11234);
    if (!ctx) {
        fprintf(stderr, "Failed to create the context: %s\n", modbus_strerror(errno));
        exit(1);
    }

    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Unable to connect: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        exit(1);
    }
    else
    {
        printf("Modbus server connected successfully\n");
    }

    //Set the Modbus address of the remote slave (to 3)
    //int rc=modbus_set_slave(ctx, 3);
    //printf("Modbus set remote slave return code : %d\n",rc);

    modbus_set_debug(ctx,FALSE);
    //uint16_t reg[5];// will store read registers values
    uint16_t tab_reg[5];// will store read registers values

    //Read 5 holding registers starting from address 10
    //int num = modbus_read_registers(ctx, 11, 3, tab_reg);
    //printf("Result of modbus_read_registers : %d\n",num);
    
    /*
    for(int i=0;i<5;i++)
    {
         printf("reg [%d] : %d\t",i+10,reg[i]);
    }
     */
    

    int ww;
    ww=modbus_read_registers(ctx,0,5,tab_reg);
    if(ww==-1){
        fprintf(stderr, "%s\n",modbus_strerror(errno));
        return -1;
    }else{
        printf("read success\n");
    }


    for(int i=0;i<5;i++){
        printf("reg[%d]=%d (0x%X)\n",i,tab_reg[i],tab_reg[i]);
    }
    
    //printf("\n");
    //if (num != 5) 
    //{// number of read registers is not the one expected
    //    fprintf(stderr, "Failed to read: %s\n", modbus_strerror(errno));
    //}



    modbus_close(ctx);
    modbus_free(ctx);
}
