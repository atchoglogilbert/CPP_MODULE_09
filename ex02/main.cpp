/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:01:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/15 08:37:33 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PMergeMe.hpp"

int main( int argc, char **argv )
{
	try
	{
		if (argc > 1)
			return (PMergeMe::sort (argv + 1));
		else
			std::cerr << "error: numbers not found" << std::endl;
	}
	catch ( const std::exception & e )
	{
		std::cerr << e.what () << std::endl;
	}
	return (1);
}
