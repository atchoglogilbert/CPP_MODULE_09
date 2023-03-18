/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PMergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:02:52 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/18 19:47:43 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_MERGE_HPP
# define P_MERGE_HPP
# include <iostream>
# include <vector>
# include <deque>
# include <time.h>
# include <set> // TODO
# include <utility> // TODO
# include <algorithm> // TODO

class PMergeMe
{
	private:
		PMergeMe( void );
		PMergeMe( PMergeMe const & p );
		PMergeMe &operator=( PMergeMe const & p );
		
		static void _sort ( std::vector<int> & vect, int begin, int end );
		static void _sort ( std::deque<int> & deque, int begin, int end );

		template<class Iterator>
		static typename std::vector<int>::iterator _print ( Iterator begin, Iterator end )
		{
			for  (Iterator it = begin; it != end; it++)
			{
				if (it - begin > 0)
					std::cout << " ";
				std::cout << *it;
			}
		}
			
	public:
		~PMergeMe( void );
		
		static int sort( char **args );

};
#endif