/* 
(c) 2020 - Robert - <dakky@dakkar.eu>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
Dieses Programm ist Freie Software: Sie können es unter den Bedingungen
der GNU General Public License, wie von der Free Software Foundation,
Version 3 der Lizenz oder (nach Ihrer Wahl) jeder neueren
veröffentlichten Version, weiterverbreiten und/oder modifizieren.
Dieses Programm wird in der Hoffnung, dass es nützlich sein wird, aber
OHNE JEDE GEWÄHRLEISTUNG, bereitgestellt; sogar ohne die implizite
Gewährleistung der MARKTFÄHIGKEIT oder EIGNUNG FÜR EINEN BESTIMMTEN ZWECK.
Siehe die GNU General Public License für weitere Details.
Sie sollten eine Kopie der GNU General Public License zusammen mit diesem
Programm erhalten haben. Wenn nicht, siehe <http://www.gnu.org/licenses/>. 
*/

/*
 *     x x x x x x x x x x x
 *     1 2 3 4 5 6 7 8 9 1 1
 *                       0 0
 *  
 * y1  E S K I S T L F Ü N F
 * y2  Z E H N Z W A N Z I G
 * y3  D R E I V I E R T E L
 * y4  T G N A C H V O R J M   xxxx
 * y5  H A L B Q Z W Ö L F P
 * y6  Z W E I N S I E B E N
 * y7  K D R E I R H F Ü N F
 * y8  E L F N E U N V I E R
 * y9  W A C H T Z E H N R S
 * y10 B S E C H S F M U H R
 */
 
 // SETUP: chose LED Wiring Layout here
#include "layout1.h"

#ifndef _WORDS_H_
#define _WORDS_H_

const int min_ONE[]      {MIN1};
const int min_TWO[]      {MIN2};
const int min_THREE[]    {MIN3};
const int min_FOUR[]     {MIN4};

const int word_ES[]      {X1Y1, X2Y1};
const int word_IST[]     {X4Y1, X5Y1, X6Y1};
const int word_UHR[]     {X9Y10, X10Y10, X11Y10};

const int word_VOR[]     {X7Y4, X8Y4, X9Y4};
const int word_NACH[]    {X3Y4, X4Y4, X5Y4, X6Y4};
const int word_VIERTEL[] {X5Y3, X6Y3, X7Y3, X8Y3, X9Y3, X10Y3, X11Y3};
const int word_HALB[]    {X1Y5, X2Y5, X3Y5, X4Y5};

const int word_EIN[]     {X3Y6, X4Y6, X5Y6};
const int word_EINS[]    {X3Y6, X4Y6, X5Y6, X6Y6};
const int word_ZWEI[]    {X1Y6, X2Y6, X3Y6, X4Y6};
const int word_DREI[]    {X2Y7, X3Y7, X4Y7, X5Y7};
const int word_VIER[]    {X8Y8, X9Y8, X10Y8, X11Y8};
const int word_FUENF1[]  {X8Y1, X9Y1, X10Y1, X11Y1};
const int word_FUENF2[]  {X8Y7, X9Y7, X10Y7, X11Y7};
const int word_SECHS[]   {X2Y10, X3Y10, X4Y10, X5Y10, X6Y10};
const int word_SIEBEN[]  {X6Y6, X7Y6, X8Y6, X9Y6, X10Y6, X11Y6};
const int word_ACHT[]    {X2Y9, X3Y9, X4Y9, X5Y9};
const int word_NEUN[]    {X4Y8, X5Y8, X6Y8, X7Y8};
const int word_ZEHN1[]   {X1Y2, X2Y2, X3Y2, X4Y2};
const int word_ZEHN2[]   {X6Y9, X7Y9, X8Y9, X9Y9};
const int word_ELF[]     {X1Y8, X2Y8, X3Y8};
const int word_ZWOELF[]  {X6Y5, X7Y5, X8Y5, X9Y5, X10Y5};
const int word_ZWANZIG[] {X5Y2, X6Y2, X7Y2, X8Y2, X9Y2, X10Y2, X11Y2};

// Special words
// WIFIMANAGER => "Wifi" Icon
const int word_WIFIMANAGER[] { 
    X4Y1, X5Y1, X6Y1, X7Y1,
    X3Y2, X4Y2, X7Y2, X8Y2,
    X3Y3, X4Y3, X7Y3, X8Y3,
    X7Y4, X8Y4,
    X6Y5, X7Y5,
    X5Y6, X6Y6,
    X5Y7, X6Y7,
    X5Y9, X6Y9,
    X5Y10, X6Y10,
    MIN1, MIN2, MIN3, MIN4};

// OTA in progress => "Arrow down" Icon
const int word_OTAPROGRESS[] { 
    X5Y1, X6Y1, X7Y1,
    X5Y2, X6Y2, X7Y2,
    X5Y3, X6Y3, X7Y3,
    X5Y4, X6Y4, X7Y4,
    X2Y5, X3Y5, X4Y5, X5Y5, X7Y5, X8Y5, X9Y5, X10Y5,
    X2Y6, X10Y6,
    X3Y7, X9Y7,
    X4Y8, X8Y8,
    X5Y9, X7Y9,
    X6Y10,
    MIN1, MIN2, MIN3, MIN4};

// OTA in succeeded => "Check mark" Icon
const int word_OTASUCCESS[] { 
    X10Y3,
    X9Y4,
    X8Y5,
    X7Y6,
    X2Y7, X6Y7,
    X3Y8, X5Y8,
    X4Y9,
    MIN1, MIN2, MIN3, MIN4};

// OTA in failed => "Cross mark" Icon
const int word_OTAERROR[] { 
    X3Y2, X4Y2, X8Y2, X9Y2,
    X4Y3, X5Y3, X7Y3, X8Y3,
    X5Y4, X6Y4, X7Y4, 
    X5Y5, X6Y5,
    X5Y6, X6Y6, X7Y6,
    X4Y7, X5Y7, X7Y7, X8Y7,
    X3Y8, X4Y8, X8Y8, X9Y8,
    MIN1, MIN2, MIN3, MIN4};

// Hourglass ....
const int word_HOURGLASS[] { 
    X2Y2, X3Y2, X4Y2, X5Y2, X6Y2, X7Y2, X8Y2, X9Y2, X10Y2,
    X3Y3, X9Y3,
    X4Y4, X8Y4,
    X5Y5, X7Y5,
    X6Y6,
    X5Y7, X7Y7,
    X4Y8, X8Y8,
    X3Y9, X9Y9,
    X2Y10, X3Y10, X4Y10, X5Y10, X6Y10, X7Y10, X8Y10, X9Y10, X10Y10,
    MIN1, MIN2, MIN3, MIN4};
#endif