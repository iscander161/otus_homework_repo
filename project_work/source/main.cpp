/**
 * @file main.cpp
 * @author Alexander Tolstunov (iscander161@yandex.ru)
 * @brief Main file of application
 * @version 0.1
 * @date 2023-01-23
 * @copyright Copyright (c) 2023
 */

/* Includes ------------------------------------------------------------------*/
#include <iostream>
#include "main.h"
#include "argv_parser.h"

/* Private function prototypes -----------------------------------------------*/
static void proj__greetings();
static void proj__argvs_handler(argv_err__e event, void* ext_data);

/**
 * @brief Enumerating application states
 */
typedef enum{
    PROJ_STATE__START = 0,      /*!< Application start */
    PROJ_STATE__ARGS,           /*!< Parsing arguments */
    PROJ_STATE__ARGS_PARSE_END, /*!< Waiting for arguments parsing end */
    PROJ_STATE__WAIT_ACTION,    /*!< Waiting for user action */
    PROJ_STATE__EXIT,           /*!< Exit application */
}proj_states__e;

/**
 * @brief Main struct of application
 */
static struct{
    proj_states__e state;       /*!< Current application state */
    int action;                 /*!< User action */
    bool wait_state;            /*!< Application wait flag */
    bool init;                  /*!< Application initialization state */
}proj_data;

/**
 * @brief Main function of application
 * @param argc Number of arguments
 * @param argvs Array of arguments
 * @return Function result
 */
int main(int argc, char** argvs)
{
    proj_data.init = false;
    proj_data.state = PROJ_STATE__START;
    while(true)
    {
        switch(proj_data.state)
        {
            case PROJ_STATE__START:
                proj__greetings();
                proj_data.state = PROJ_STATE__ARGS;
                break;
            case PROJ_STATE__ARGS:
                if(argc == 0x01)
                    std::cout << "No arguments found" << std::endl;
                else
                {
                    proj_data.wait_state = true;
                    proj_data.state = PROJ_STATE__ARGS_PARSE_END;
                    argv_parser__start(argc, argvs, proj__argvs_handler);
                }
                proj_data.state = PROJ_STATE__WAIT_ACTION;
                break;
            case PROJ_STATE__ARGS_PARSE_END:
                if(proj_data.wait_state)
                    break;
                proj_data.state = PROJ_STATE__WAIT_ACTION;
                [[fallthrough]];
            case PROJ_STATE__WAIT_ACTION:
                std::cout << "Make your choise: ";
                std::cin >> proj_data.action;
                if(proj_data.action == ACTION__EXIT)
                    proj_data.state = PROJ_STATE__EXIT;
                break;
            case PROJ_STATE__EXIT:
                std::cout << "Your choise: " << proj_data.action << std::endl;
                return EXIT_SUCCESS;
            default:
                //TODO Need to make an error parser
                break;
        }
    }
}

/**
 * @brief Application greetings function
 */
static void proj__greetings()
{
    for(int i = 0; i < 80; i++)
        std::cout << "=";
    std::cout << std::endl << "=";
    for(int i = 0; i < 29; i++)
        std::cout << " ";
    std::cout << "Project Work v0.0.1";
    for(int i = 0; i < 30; i++)
        std::cout << " ";
    std::cout << "=" << std::endl;
    for(int i = 0; i < 80; i++)
        std::cout << "=";
    std::cout << std::endl;
}

static void proj__argvs_handler(argv_err__e event, void* ext_data)
{
    (void)ext_data;
    switch(event)
    {
        case ARGV_ERR__OK:
            proj_data.wait_state = false;
            break;
        case ARGV_ERR__ERROR:
        default:
            break;
    }
}
