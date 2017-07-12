/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_code.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flefebvr <flefebvr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/04/14 15:54:35 by flefebvr          #+#    #+#             */
/*   Updated: 2016/04/14 15:54:38 by flefebvr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_CODE_H
# define MLX_CODE_H

# define KEYPRESS 2
# define KEYPRESSMASK (1L<<0)
# define KEYRELEASE 3
# define KEYRELEASEMASK (1L<<1)
# define BUTTONPRESS 4
# define BUTTONPRESSMASK (1L<<2)
# define BUTTONRELEASE 5
# define BUTTONRELEASEMASK (1L<<3)
# define MOTIONNOTIFY 6
# define POINTERMOTIONMASK (1L<<6)
# define FOCUSOUT 10
# define FOCUSCHANGEMASK (1L<<21)
# define EXPOSE 12
# define NOEXPOSE 14
# define EXPOSUREMASK (1L<<15)

# define KEY_ESC 65307
# define KEY_F1 65470
# define KEY_F2 65471
# define KEY_F3 65472
# define KEY_F4 65473
# define KEY_F5 65474
# define KEY_F6 65475
# define KEY_F7 65476
# define KEY_F8 65477
# define KEY_F9 65478
# define KEY_F10 65479
# define KEY_F11 65480
# define KEY_F12 65481
# define KEY_Q 97
# define KEY_W 122
# define KEY_E 101
# define KEY_R 114
# define KEY_A 113
# define KEY_S 115
# define KEY_D 100
# define KEY_F 102
# define KEY_C 99
# define KEY_SPACE 32
# define KEY_SHIFT 65505
# define KEY_DELETE 65288
# define KEYPAD_0 65438
# define KEYPAD_1 65436
# define KEYPAD_2 65433
# define KEYPAD_3 65435
# define KEYPAD_4 65430
# define KEYPAD_5 65437
# define KEYPAD_6 65432
# define KEYPAD_7 65429
# define KEYPAD_8 65431
# define KEYPAD_9 65434
# define KEY_PLUS 65451
# define KEY_MINUS 65453
# define KEYPAD_DOT 65439

# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_LEFT_CLICK 1
# define MOUSE_RIGHT_CLICK 2

#endif
