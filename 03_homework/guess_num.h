/**
 * @file guess_num.h
 * @author Alexander Tolstunov (iscander161@yandex.ru)
 * @brief 
 * @version 0.1
 * @date 2023-01-23
 * 
 * @copyright Copyright (c) 2023
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _GUESS_NUM_H_
#define _GUESS_NUM_H_

/* Includes ------------------------------------------------------------------*/
#include <string>

/* Public constant variables -------------------------------------------------*/
const int DEFAULT_MAX_VALUE                     = 101;  /*!< Deafult random value*/
const unsigned int GAME_PARAM__SHOW_TABLE       = 2;    /*!< Show table of highscores */

#if defined(_WIN32)
const char SLASH_FOR_PATH = '\\';   /*!< Slash for Windows path */
#else
const char SLASH_FOR_PATH = '/';    /*!< Slash for Unix-based OS */
#endif  /* SLASH FOR PATH */

/**
 * @brief Game initialization
 * @param game_param Game parameters
 * @param level Game level (Default value = 0).
 */
void guess_num__init_game(std::string score_file_path, unsigned int max_val, unsigned int level, int game_param);

#endif /* _GUESS_NUM_H_ */
