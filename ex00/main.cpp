/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:57:32 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/15 00:18:53 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "BitcoinExchange.hpp"

int main(int argc, char **argv)
{
	try
	{
		if (argc == 2)
			return (BitcoinExchange::toBitcoin ("data.csv", argv[1]));
		else
			BitcoinExchange::_putError ("invalid number of arguments");
	}
	catch ( const std::exception & e)
	{
		std::cerr << e.what () << std::endl;
	}
	return (1);
}
