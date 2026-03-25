/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: inhlee <inhlee@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/20 19:33:12 by inhlee            #+#    #+#             */
/*   Updated: 2025/07/21 17:54:29 by inhlee           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>    
#include <stdio.h>    
#include <stdlib.h>    
#include <unistd.h>
  
int main()
{
    char *line;
    int fd;

    fd = open("test.txt",O_RDONLY);
    while((line = get_next_line(fd)))
    {
        printf("%s",line);
        free(line);
    }
    close(fd);
    return 0;
}



