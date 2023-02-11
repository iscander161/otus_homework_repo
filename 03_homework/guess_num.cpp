/**
 * @file guess_num.cpp
 * @author Alexander Tolstunov (iscander161@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2023-01-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* Includes ------------------------------------------------------------------*/
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include "guess_num.h"

/*Private function prototypes ------------------------------------------------*/
static void guess_num__play_game(int max_value, unsigned int level = 3);
static void guess_num__show_record_table();
static void guess_num__update_record_table(std::string username, int attempts);
static void guess_num__check_score_file();

std::string score_file_pth; /*!< Score File path*/

/**
 * @brief Init game function
 * 
 * @param score_file_path Path to score file
 * @param max_val Maximum value of secret number
 * @param level Game level
 * @param game_param Game parameters
 */
void guess_num__init_game(std::string score_file_path, unsigned int max_val, unsigned int level, int game_param)
{
    (void)level;
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
    /* Combine score file path */
    size_t ind = score_file_path.find_last_of(SLASH_FOR_PATH);
    score_file_path.erase(ind);
    std::cout << score_file_pth << std::endl;
    score_file_pth = score_file_path + SLASH_FOR_PATH + "record_table.txt";
    guess_num__check_score_file();
    switch(game_param)
    {
    case GAME_PARAM__SHOW_TABLE:
        guess_num__show_record_table();
        return;
        break;
    default:
        guess_num__play_game(max_val, level);
        return;
    }
}

/**
 * @brief Play game function
 * @param max_value 
 */
static void guess_num__play_game(int max_value, unsigned int level)
{
    int attempts = 0;
    int secret_number;
    int random_value;
    std::string user_name;

    switch (level)
    {
    case 0:
        random_value = max_value + 1;
        break;
    case 1:
        random_value = 11;
        break;
    case 2:
        random_value = 51;
        break;    
    case 3:
    default:
        random_value = DEFAULT_MAX_VALUE;
        break;
    }
    
    std::cout << "Level is ";
    if(!level) std::cout << "user.";
    else std::cout << level << ".";
    std::cout << " Maximum value is " << random_value - 1 << std::endl;

    secret_number = std::rand() % random_value;
    std::cout << "Hi! Enter your name, please:" << std::endl;
    std::getline(std::cin, user_name);
    while(secret_number != random_value)
    {
        ++attempts;
        std::cout << "Enter your guess:" << std::endl;
        std::cin >> random_value;
        if(secret_number < random_value)
            std::cout << "Less than " << random_value << ". ";
        else if(secret_number > random_value)
            std::cout << "Greater than " << random_value  << ". ";

    }
    std::cout << "You win! Attempts = " << attempts << std::endl << std::endl;
    guess_num__update_record_table(user_name, attempts);
    guess_num__show_record_table();
}

/**
 * @brief Score table display function
 */
static void guess_num__show_record_table()
{
    std::ifstream score_file(score_file_pth);
    std::string get_score_line;
    long int size_of_file;
    if(!score_file.is_open())
    {
        std::cout << "Error open record table" << std::endl;
    }
    else
    {
        score_file.seekg(0, std::ios_base::end);
        size_of_file = static_cast<long>(score_file.tellg());
        score_file.seekg(std::ios_base::beg);
        std::cout << "Record table";
        if(!size_of_file)
         std::cout << " is empty." << std::endl;
        else
        {
            std::cout << std::endl;
            while(getline(score_file, get_score_line))
                std::cout << get_score_line << std::endl;
        }
    }
    score_file.close();
}

/**
 * @brief Score table update function
 * @param username Name of user
 * @param attempts Attempts
 */
static void guess_num__update_record_table(std::string username, int attempts)
{
    std::string file_content;
    std::string user_exist_str;
    std::fstream score_file(score_file_pth, std::ios_base::in);    
    size_t position_of_user_name = 0;
    size_t position_of_attempt = 0;
    int old_attempt = 0;
    size_t size_of_attempts;
    size_t size_of_old_string = 0;

    if(score_file.is_open())
    {
        while(getline(score_file, user_exist_str))
        {
            file_content += user_exist_str += '\n';
        }

        position_of_user_name = file_content.find(username);

        if(position_of_user_name == static_cast<size_t>(-1))
        {
            position_of_user_name = file_content.length();            
            user_exist_str = username + " " + std::to_string(attempts) + '\n';
            size_of_old_string = user_exist_str.length() - 1;
        }
        else
        {
            if(size_t index = file_content.find_last_of("\n"); index != std::string::npos)
                file_content.erase(index);
            size_of_old_string = file_content.find_first_of('\n', position_of_user_name) - position_of_user_name;
            user_exist_str.clear();
            user_exist_str = file_content.substr(position_of_user_name, size_of_old_string);
        }
        score_file.close();
    }
    else
        std::cout << "Error open record table" << std::endl;
    
    position_of_attempt = user_exist_str.find_last_of(' ') + 1;    
    size_of_attempts = user_exist_str.length() - position_of_attempt;
    old_attempt = atoi(&user_exist_str[position_of_attempt]);

    /*
    // Code to clear the table. Not needed if the file correct.
    if(!old_attempt)
    {
        std::cout << "Error in record table" << std::endl;
        score_file.open(score_file_pth,
                            std::ios_base::out);
        if(score_file.is_open())
        {
            score_file.clear();
            score_file.close();
        }
        guess_num__update_record_table(username, attempts);
    }
    */

    if(attempts <= old_attempt)
    {
        score_file.open(score_file_pth, std::ios_base::out);

        if(score_file.is_open())
        {
            user_exist_str.erase(position_of_attempt, size_of_attempts);
            user_exist_str.append(std::to_string(attempts));
            file_content.replace(position_of_user_name, size_of_old_string, user_exist_str);
            score_file.write(file_content.c_str(), file_content.length());
        }
    }
    score_file.close();
}

static void guess_num__check_score_file()
{
    std::ofstream score_file(score_file_pth, std::ios::app);
    if(score_file.is_open())
    {
        score_file.close();
    }
}
