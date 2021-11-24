#include <stdio.h>
#include <fcntl.h>   /* File Control Definitions           */
#include <termios.h> /* POSIX Terminal Control Definitions */
#include <unistd.h>  /* UNIX Standard Definitions      */
#include <errno.h>   /* ERROR Number Definitions           */
#include <sys/ioctl.h>
#include <stdlib.h>
#include "modbus.h"
#include <string.h>
int main()
{
    printf("Modbus slave example\n");
    //Prepare a Modbus mapping with 30 holding registers
    //(plus no output coil, one input coil and two input registers)
    //This will also automatically set the value of each register to 0
    modbus_mapping_t *mapping=NULL;
    modbus_t* ctx=NULL;
    int s=-1;
    int ret=0;

    uint8_t query[MODBUS_TCP_MAX_ADU_LENGTH];

    /*
    if (!mapping) {
        fprintf(stderr, "Failed to allocate the mapping: %s\n", modbus_strerror(errno));
        exit(1);
    }
    else
    {
        printf("Mapping allocated successfully.\n");
    }
    */


    //Example: set register 12 to integer value 623
    //mapping->tab_registers[12] = 623;


    ctx = modbus_new_tcp("127.0.0.1",11234);
    if (NULL==ctx) {
        fprintf(stderr, "Failed to create the context: %s\n", modbus_strerror(errno));
        exit(1);
    }else{
        printf("Set up TCP Message success \n");
    }


    s=modbus_tcp_listen(ctx,1);
    modbus_tcp_accept(ctx,&s);


    //Set the Modbus address of this slave (to 3)
   //int rc= modbus_set_slave(ctx, 3);
   //printf("Result code of Modbus set slave address :%d\n",rc);

    
   /*
    if (modbus_connect(ctx) == -1) {
        fprintf(stderr, "Unable to connect: %s\n", modbus_strerror(errno));
        modbus_free(ctx);
        exit(1);
    }
    else
    {
        printf("Modbus slave connected successfully\n");
    }
    
    */

    mapping=modbus_mapping_new(0,0,10,0);
    if(NULL==mapping){
        fprintf(stderr,"Error: mapping %s\n",modbus_strerror(errno));
        modbus_free(ctx);
        return 1;
    }


    mapping->tab_registers[0] = 101;
    mapping->tab_registers[1] = 103;
    mapping->tab_registers[2] = 104;
    mapping->tab_registers[3] = 65000;
    mapping->tab_registers[4] = 3;
    mapping->tab_registers[5] = 53;


    //modbus_set_debug(ctx,TRUE);
    /*
    sockfd=modbus_tcp_listen(ctx,1);
    if(-1==sockfd){
        printf("modbus_tcp_listen failed...\n");
        modbus_free(ctx);
        return 1;
    }

    ret=modbus_tcp_accept(ctx,&sockfd);
    if(-1==ret){
        printf("modbus_tcp_accpet failed : %s\n",modbus_strerror(errno));
        modbus_free(ctx);
        return 1;
    } */

    int rep=-1;

    printf("\nwaitwait\n");

    while(1) {
        memset(query,0,sizeof(query));
        ret = modbus_receive(ctx, query);

        if(ret >= 0){
            printf("Modbus receive len : %d\n",ret);
            rep=modbus_reply(ctx,query,ret,mapping);
            printf("query: %X\n",*query);
            printf("Modbus receive len : %d\n",ret);
            //printf("mapping->tab_registers[0]: %d\n",mapping->tab_registers[0]);
            printf("Modbus reply len : %d\n",rep);
            printf("\n");
        }else{
            //printf("connection close");
            //modbus_close(ctx);

            //waiting 
            modbus_tcp_accept(ctx,&s);
        }

    }


        //len1 = modbus_reply(ctx, req, len, mapping);
        //printf("req: %X\n",*req);
        //printf("len : %d\n",len);
        //printf("mapping->tab_registers[12] : %d\n",mapping->tab_registers[12]);

        //if (len == -1) break;
    //}
    printf("Exit the loop: %s\n", modbus_strerror(errno));

    modbus_mapping_free(mapping);
    modbus_close(ctx);
    modbus_free(ctx);
}
