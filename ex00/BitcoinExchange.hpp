/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: katchogl <katchogl@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/03 09:58:11 by katchogl          #+#    #+#             */
/*   Updated: 2023/03/19 06:46:32 by katchogl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITCOIN_EXCHANGE_HPP
# define BITCOIN_EXCHANGE_HPP
# include <iostream>
# include <string>
# include <fstream>
# include <map>
# include <utility>

class Date
{
	private:
		int _year;
		int _month;
		int _day;
		std::string _date;

	public:
		Date( void );
		Date( std::string s );
		Date( const Date & d );
		Date &operator=( const Date & d );
		~Date( void );

		// getters
		const int &getYear( void ) const;
		const int &getMonth( void ) const;
		const int &getDay( void ) const;
		const std::string &getDate( void ) const;

		// utils
		bool operator==( const Date & d ) const;
		bool operator<( const Date & d ) const;
		bool operator>( const Date & d ) const;
};

std::ostream &operator<<(std::ostream & stream, const Date & d);

class BitcoinExchange
{
	private:
		BitcoinExchange( void );
		BitcoinExchange ( const BitcoinExchange & b );
		BitcoinExchange &operator=( const BitcoinExchange & b );

		static bool _hasValidSpacing( std::string ln );
		static bool _isEmpty( std::string s );
		static std::string _trim( std::string s );
		static bool _isValidDate( const Date & d );
		static std::map<Date, double> _parse ( std::string dbPathn );

	public:
		~BitcoinExchange( void );

		static int _putError( std::string err );
		static int	toBitcoin( std::string dbPathn, std::string amountsPathn );
};
#endif