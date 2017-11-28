/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   City.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/28 12:16:58 by NoobZik           #+#    #+#             */
/*   Updated: 2017/11/28 12:16:58 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* ========================================================================= *
 * City interface
 * ========================================================================= */

#ifndef _CITY_H_
#define _CITY_H_

/** Data structure for storing city information */
typedef struct city_t {
    char* name;
    double latitude; // latitude
    double longitude; // longitude
} City;

#endif // !_CITY_H_
