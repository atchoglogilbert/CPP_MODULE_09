/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/05 12:08:59 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/19 04:23:38 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN( void ) {}

RPN::RPN( RPN const & rpn ) { (void) rpn; }

RPN &RPN::operator=( RPN const & rpn ) { (void) rpn; return (*this); }

RPN::~RPN( void ) {}

bool RPN::_is_single_op ( const std::string & expr, size_t i )
{
	while (expr[++i])
		if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*'
			|| expr[i] == '/')
			return (false);
	return (true);
}

void RPN::_calculate ( std::stack<int> & lvls, const std::string & expr, const size_t & i )
{
	std::string	s;
	int 		high;
	int 		res;

	if (lvls.size () < 2)
		return ;
	high = lvls.top ();
	lvls.pop ();
	if (lvls.size () > 1 && _is_single_op (expr, i)) // handle insufficient operators
	{
		s = "";
		while (lvls.size () > 0)
		{
			s = std::to_string (lvls.top ()) + s;
			lvls.pop ();
		}
		lvls.push (std::stoi (s));
	}
	if (expr[i] == '+' || i == expr.length ()) // to handle eof
		res = lvls.top () + high;
	else if (expr[i] == '-')
		res = lvls.top () - high;
	else if (expr[i] == '*')
		res = lvls.top () * high;
	else if (expr[i] == '/')
		res = lvls.top () / high;
	lvls.pop ();
	lvls.push (res);
}

int RPN::calc( const std::string & expr )
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
			if (lvls.size () == 1 && expr[i] == '-') // if already empty, either sign or someone is trying to fuck w/ my program
			{
				temp = lvls.top ();
				lvls.pop ();
				lvls.push (-temp);
			}
			else if (lvls.size () == 1 && (expr[i] == '*' || expr[i] == '/')) // handle multiplication and division with invalid count of operands
			{
				lvls.pop ();
				lvls.push (0);
			}
			else if (!(lvls.size () == 1 && expr[i] == '+')) // if not simple plus
				_calculate (lvls, expr, i);
		}
		else if (expr[i] >= '0' && expr[i] <= '9')
		{
			if (lvls.size () == 1 && lvls.top () == 0) // remove init res
				lvls.pop ();
			lvls.push (expr[i] - '0');
		}
		else if (expr[i] != ' ')
			throw UnsupportedCharacter ();
		i++;
	}
	if (lvls.size () != 1)
		throw InternalError ();
	return (lvls.top ());
}

const char *RPN::UnsupportedCharacter::what( void ) const throw()
{
	return ("unsupported character");
}

const char *RPN::InternalError::what( void ) const throw()
{
	return ("internal error");
}
