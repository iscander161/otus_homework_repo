/**
 * @file main.c
 * @author Alexander Tolstunov (iscander161@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2023-01-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* Includes ------------------------------------------------------------------*/
#include <iostream>
#include <string>
#include "main.h"
#include "guess_num.h"

/* Private function prototypes -----------------------------------------------*/
static int arg_type(char* argv);
static unsigned int guess_the_number__parse_args(int argc, char** argvs, int* game_parameter = nullptr, int* game_level = nullptr);

/**
 * @brief Main function of application
 * @param argc Arguments 
 * @param argvs Arguments of application
 * @return int Result of application
 * @retval !0 - Some error occured
 */
int main(int argc, char** argvs)
{
    unsigned int max_value = DEFAULT_MAX_VALUE;
    int game_parameter = 0;
    int game_level = 3;

    std::cout << "Guess the Number Game v0.2" << std::endl;

    if(argc > 1)
        max_value = guess_the_number__parse_args(argc, argvs, &game_parameter, &game_level);
    
    if(game_level == -1)
    {
        return EXIT_SUCCESS;
    }

    guess_num__init_game(argvs[0], max_value, game_level, game_parameter);

    return EXIT_SUCCESS;
}

/**
 * @brief Params of main function passed to this function
 * @param argc Arguments 
 * @param argvs Arguments of application
 * @return int - Maximum value of random value
 */
static unsigned int guess_the_number__parse_args(int argc, char** argvs, int* game_parameter, int* game_level)
{
    unsigned int max_value = DEFAULT_MAX_VALUE;

    if(argc < 2)
        return max_value;

    for(int i = 1; i < argc; i++)
    {
        switch(arg_type(argvs[i]))
        {
        case ARG_TYPE__MAX_VALUE:
            if((i + 1) >= argc)
            {
                std::cout << "Error parsing arguments" << std::endl;
                return max_value;
            }
            max_value = atoi(std::string(argvs[++i]).c_str());
            if(!max_value)
            {
                std::cout << "Error read max value. Default value is " << DEFAULT_MAX_VALUE - 1 << std::endl;
                max_value = DEFAULT_MAX_VALUE;
            }
            else if(max_value > RAND_MAX)
            {
                std::cout << "Your number is greater than max. Default value is " << DEFAULT_MAX_VALUE - 1 << std::endl;
                max_value = DEFAULT_MAX_VALUE;
            }
            if(game_level)
                *game_level = 0;
            break;
        case ARG_TYPE__TABLE:
            if(game_parameter)
                *game_parameter = GAME_PARAM__SHOW_TABLE;
            break;
        case ARG_TYPE__LEVEL:
            if((i + 1) >= argc)            
            {
                std::cout << "Error parsing arguments" << std::endl;
                if(game_level)
                    *game_level = -1;
            }
            else
            {
                if(game_level)
                    *game_level = atoi(std::string(argvs[++i]).c_str());
                if(!*game_level)
                {
                    std::cout << "Error read level. Default level is " << 3 << std::endl;
                    if(game_level)
                        *game_level = 3;
                }
            }
            break;
        default:
            std::cout << "Argument unsuported. Exit application." << std::endl;
            if(game_parameter)
            *game_parameter = -1;
        }
    }
    return max_value;
}

/**
 * @brief Finding an argument
 * @param argv - Argument
 * @return int - Argument type
 */
static int arg_type(char* argv)
{
    if(std::string(argv).find("max") != std::string::npos)
        return ARG_TYPE__MAX_VALUE;
    else if(std::string(argv).find("level") != std::string::npos)
        return ARG_TYPE__LEVEL;
    else if (std::string(argv).find("table") != std::string::npos)
        return ARG_TYPE__TABLE;
    return -1;
}
