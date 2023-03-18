/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:20:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/18 20:17:52 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
# define RPN_HPP
# include <iostream>
# include <stack>

class RPN
{
	private:
		RPN( void );
		RPN( RPN const & rpn );
		RPN &operator=(RPN const & rpn );
		~RPN( void );
	
	public:
		static int calc( const std::string & expr );
		static void _calculate( std::stack<int> & lvls, const std::string & expr, const size_t & i );

	class InvalidCharacter: public std::exception
	{
		public:
			const char *what( void ) const throw();
	};

	class InternalError: public std::exception
	{
		public:
			const char *what( void ) const throw();
	};
};
#endif