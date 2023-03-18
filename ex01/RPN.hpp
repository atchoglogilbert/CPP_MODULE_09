/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 14:20:06 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/05 13:59:34 by katchogl         ###   ########.fr       */
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
		static		int calc( std::string expr );

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