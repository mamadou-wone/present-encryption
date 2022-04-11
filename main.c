#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "param.h"
#include "present.h"
#include "time.h"

/**
* Ici on fait l'allocation dynamique de la m�moire avec calloc pour mettre les valeur � z�ro
*/
void init(){
    state = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );
    register_key = (uint8_t *) calloc( PRESENT_KEY_SIZE, sizeof(uint8_t) );
    round_key = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );

}

void keygen(){
    time_t t;
    register_key = (uint8_t *) calloc( PRESENT_KEY_SIZE, sizeof(uint8_t) );
    srand((unsigned) time(&t));
    int i=0;
    for( i = 0 ; i < PRESENT_KEY_SIZE ; i++ ) {
        register_key[i]=(uint8_t)rand();
    }
}

void sub_key(){
//    ASSERT(NULL != register_key);
    round_key = (uint8_t *) calloc( PRESENT_CRYPT_SIZE, sizeof(uint8_t) );
    int i=0;
    for( i = 2 ; i < PRESENT_KEY_SIZE ; i++ ) {
        round_key[i-2]=register_key[i];
    }
}

void add_round_key(){
    // ASSERT(NULL != state);
    //ASSERT(NULL != round_key);
    int i=0;
    for(i=0; i<PRESENT_CRYPT_SIZE ; i++ ){
        state[i]=state[i]^round_key[i];
    }
}

void print_byte(uint8_t * bytes, int size){
    int i=0;
    printf("\n");
    for(i=size-1; i >= 0; i--)
        printf("%d ", bytes[i]);
    printf("\n");
}

int main() {

    int i = 0;
    init();
    keygen();
    sub_key();
    print_byte(register_key, PRESENT_KEY_SIZE);
    print_byte(round_key, PRESENT_CRYPT_SIZE);
    uint8_t state1[] = {0xF1,0xF1,0xF1,0xF1,0xF1,0xF1,0xF2,0xF1};
    memcpy( state, state1, PRESENT_CRYPT_SIZE );
    add_round_key();

    //print_byte(state, PRESENT_CRYPT_SIZE);
    return 0;
}
