/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:22:57 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/05 15:01:22 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main( int argc, char **argv )
{
	int	res;
	
	try
	{
		if (argc < 3)
		{
			if (argc == 2)
				res = RPN::calc (argv[1]);
			else
				res = RPN::calc ("");
			std::cout << res << std::endl;
		}
		else
			std::cout << "too many arguments" << std::endl;
	}
	catch (std::exception const & e )
	{
		std::cout << e.what () << std::endl;
	}
	return (0);
}
