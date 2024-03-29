//Stock Ticker - Provides stock prices based on symbols provided from arguments
//Copyright(C) 2023 TxMedic435
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <curl/curl.h>
#include "stock.h"
#include "options.h"

//COLORED OUTPUT 
#define RED "\033[31m"
#define GREEN "\033[32m"
#define RESET "\033[0m"

//UNICODE 
const std::string UP_ARROW = "\u2191";
const std::string DOWN_ARROW = "\u2193";

int main(int argc, char* argv[]){
	std::vector<Stock> stocks;							//Will store classes for each ticker symbol.
	
	if(argc < 2){
		PrintHelp();
		
		return 1;
	}

	else {
		std::vector<std::string> args;						//Stores the symbols names provided by user
		
		//Parse each symbol from arguments and create a Stock instance of it.
		for(int i = 1; i < argc; i++){
			if(i ==1 ){
				std::cout << "Symbol\t\tPrice\t\tChange\t\tChange(%)\tVolume\n";
			}
			std::string sym(argv[i]);
			Stock temp(sym);
			if(temp.GetCurrentPrice() < 0){					//Ignore invalid symbols
				continue;
			}

			else {
				float priceChange = temp.GetCurrentPrice() - temp.GetOpen();
				
				//Print symbol and current price
				std::cout << temp.GetSymbol() << "\t\t$" << std::setprecision(2) << std::fixed << temp.GetCurrentPrice() << "\t\t";
				if(priceChange > 0){
					std::cout << GREEN << UP_ARROW << " $";
				}
				if(priceChange < 0){
					std::cout <<  RED << DOWN_ARROW << " $";
				}
				if(priceChange == 0){
					std::cout << "  $";
				}
				
				//Print change in dollar amount
				std::cout << std::setprecision(2) << std::fixed << temp.GetCurrentPrice() - temp.GetOpen() << RESET <<"\t";
				if(priceChange == 0){
					std::cout << "\t";
				}

				//Print change in percentage
				float percent = 100 * (temp.GetCurrentPrice() - temp.GetOpen()) / temp.GetOpen();
				if(percent < 0){
					std::cout << RED;
				}
				if(percent > 0){
					std::cout << "\t" << GREEN;
				}
				std::cout << std::setprecision(2) << std::fixed << percent << "%" << RESET << "\t\t";

				//Print volume
				std::cout << temp.GetVolume() << std::endl;

			}
		}

	}

	return 0;
}

//Stock quote url (current quote)
//https://query1.finance.yahoo.com/v10/finance/quoteSummmary/ /symbol?modules=price

//Stock quote url (current quote)
//https://query1.finance.yahoo.com/v8/finance/chart/ /symbol?interval=2m

//Historical data CSV download
//https://query1.finance.yahoo.com/v7/finance/download + /symbol + ?period1= + /date1 + &period2= + /date2 + &interval= /interval + &events=history
