/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PMergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 16:02:52 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/19 05:29:06 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef P_MERGE_HPP
# define P_MERGE_HPP
# include <iostream>
# include <vector>
# include <list>
# include <time.h>
# include <utility>
# include <algorithm>

class PMergeMe
{
	private:
		PMergeMe( void );
		PMergeMe( PMergeMe const & p );
		PMergeMe &operator=( PMergeMe const & p );

		static int _at ( std::list<int> & li, int index );
		static void _assign ( std::list<int> & li, int index, int val );
		static std::list<int>::iterator _it ( std::list<int> & li, int index );
		
		static void _sort ( std::vector<int> & vect, int begin, int end );
		static void _sort ( std::list<int> & li, int begin, int end );

	public:
		~PMergeMe( void );
		
		static int sort( char **args );

};
#endif