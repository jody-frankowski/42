/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   sudoku.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: jfrankow <jfrankow@student.le-101.>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/07/15 21:41:31 by jfrankow     #+#   ##    ##    #+#       */
/*   Updated: 2018/07/15 21:41:32 by jfrankow    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef SUDOKU_H
# define SUDOKU_H

int		is_valid_grid(char sudoku[9][9]);
int		is_valid(char sudoku[9][9], int i, int j);

#endif
