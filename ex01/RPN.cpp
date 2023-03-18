/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:08:59 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/15 08:05:44 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN( void ) {}

RPN::RPN( RPN const & rpn ) { (void) rpn; }

RPN &RPN::operator=( RPN const & rpn ) { (void) rpn; return (*this); }

RPN::~RPN( void ) {}

int RPN::calc( std::string expr )
{
	std::stack<int> 	lvls; // RPN calc levels
	size_t				i;
	int					temp;

	i = 0;
	lvls.push (0); // init result
	while (i < expr.length () + 1) // until eof string to handle no op and override that default addition
	{
		if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/'
			|| i == expr.length ())
		{
			temp = lvls.top (); // first operand, operation not possible so res is atm eq to first operand
			lvls.pop ();
			if (lvls.empty () && expr[i] == '-') // if already empty, either sign or someone is trying to fuck w/ my program
				temp = -temp;
			else if (lvls.empty () && (expr[i] == '*' || expr[i] == '/')) // handle multiplication and division with invalid count of operands
				temp = 0;
			else
			{
				while (!lvls.empty ())
				{
					if (expr[i] == '+' || i == expr.length ()) // to handle eof
						temp = lvls.top () + temp;
					else if (expr[i] == '-')
						temp = lvls.top () - temp;
					else if (expr[i] == '*')
						temp = lvls.top () * temp;
					else if (expr[i] == '/')
						temp = lvls.top () / temp;
					lvls.pop ();
				}
			}
			lvls.push (temp);
		}
		else if (expr[i] >= '0' && expr[i] <= '9')
		{
			if (lvls.size () == 1 && lvls.top () == 0) // remove init res
				lvls.pop ();
			lvls.push (expr[i] - '0');
		}
		else if (expr[i] != ' ')
			throw InvalidCharacter ();
		i++;
	}
	if (lvls.size () != 1)
		throw InternalError ();
	return (lvls.top ());
}

const char *RPN::InvalidCharacter::what( void ) const throw()
{
	return ("invalid character");
}

const char *RPN::InternalError::what( void ) const throw()
{
	return ("internal error");
}
