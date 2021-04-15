/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include <string.h>

#include "mbed.h"


//Draft for the code in assignment 8 Threads and mutexes

//Requirements for the assignment:
//1. 10% Create a struct with three variables: A minute counter, a second counter and a mutex
//2. 05% Create an instance of the struct in the main() function
//3. 20% Create three threads. Increase the priority of the first two
//4. 20% Lock the mutex in the three threads so only one thread can access it at a time
//5. 15% Increase the minute counter once per minute in the first thread
//6. 15% Increase the second counter once per second in the second thread
//7. 15% Print the current clock value twice per second in the third thread





//Struct for sharing data between threads

// 1. Have I done the setup here correctly?

struct Data {
    Mutex mutex;
    uint8_t minute = 0;
    uint8_t second = 0;
} data;


//Thread 1 Minute_counter
//General idea of how the minute counter works

//2. It doesn't recognize the second data perimeter here (the one without pointer), 
//have I written it wrong, or should there be another parameter here?

void minutes (Data*, data){
    while(true) {

        //it doesn't recognize data here in the mutex either...

        data->mutex.lock();

        //3. am I allowed to write it like this in mbed?

        int minute += 1;

        data->mutex.unlock();

        //since it sleeps for 60s, the idea is that it will udate every sleep cycle
        //4. does this idea work at all? 
        //(something went wrong in the setup, so I can't edit mbed-app.json,which means no testing)

        ThisThread::sleep_for(60s);

        //5. do we need to limit this for values above 60, or is it alright to just have it like this?
    }
}



//Thread 2 Second counter
//General idea of how the second_counter works

//Same questions for this thread as the thread above, if you could answer for one of them I can adjust the other one too

void seconds (Data* data){
    while(true){
        data->mutex.lock();
        int second += 1;
        data->mutex.unlock();

        //since it sleeps for 1s, it will update seconds every sleep cycle is the idea
        ThisThread::sleep_for(1s);
    }
}


//Thread 3 Printing out the clock values

//same problem with data here, as you can imagine

void printer (Data* data){
    while(true){
        data->mutex.lock();

        //6. am I allowed to use a print statement like this in mbed, or do I need to set it up differently?

        printf("Current value:\n %i : %i", minute, second);
        data->mutex.unlock();

        //since it sleeps for 500ms, the idea is that it will run every 0.5 seconds
        ThisThread::sleep_for(500ms);
    }
}


int main()
{

//Initializing the struct in main
    struct Data data;


//Create threads
    Thread minutes_thread;
    Thread seconds_thread;
    Thread printer_thread;

//Start threads

//7. another issue with data here, is it the same issue as above?
    minutes_thread.start(callback(minutes, &data));
    seconds_thread.start(callback(seconds, &data));
    printer_thread.start(callback(printer, &data));

//setting higher priority for the minute and second counter
    minutes.set_priority(osPriorityAboveNormal);
    seconds.set_priority(osPriorityAboveNormal);

//8. is there anything else I have to remember to put in main here?

}
