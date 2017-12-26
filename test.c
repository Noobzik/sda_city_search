/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: NoobZik <rakib.hernandez@gmail.com>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/26 20:12:38 by NoobZik           #+#    #+#             */
/*   Updated: 2017/12/26 20:24:32 by NoobZik          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "zscore.h"
#include "City.h"
#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[]) {
  (void) argc;
  (void) argv;
  City   city;
  uint64_t max;
  uint64_t min;
  uint64_t coded;


  city.name = malloc(sizeof(char)*12);
  city.latitude = 3.45;
  city.longitude = 11.2;
  strcpy(city.name, "osoe bekada");

  max = zEncode(10,10);
  min = zEncode(1,1);
  coded = zEncode(city.latitude, city.longitude);

  printf("Minimum : %"PRIu64"\n", min);
  printf("Maximum : %"PRIu64"\n", max);
  printf("Encodage : %"PRIu64"\n", coded);
  free(city.name);
  return 0;
}
