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

# define KEY_ESC 53
# define KEY_F1 122
# define KEY_F2 120
# define KEY_F3 99
# define KEY_F4 118
# define KEY_F5 96
# define KEY_F6 97
# define KEY_F7 98
# define KEY_F8 100
# define KEY_F9 101
# define KEY_F10 109
# define KEY_F11 103
# define KEY_F12 111
# define KEY_Q 12
# define KEY_W 13
# define KEY_E 14
# define KEY_R 15
# define KEY_A 0
# define KEY_S 1
# define KEY_D 2
# define KEY_F 3
# define KEY_C 8
# define KEY_SPACE 49
# define KEY_SHIFT 257
# define KEY_DELETE 51
# define KEYPAD_0 82
# define KEYPAD_1 83
# define KEYPAD_2 84
# define KEYPAD_3 85
# define KEYPAD_4 86
# define KEYPAD_5 87
# define KEYPAD_6 88
# define KEYPAD_7 89
# define KEYPAD_8 91
# define KEYPAD_9 92
# define KEYPAD_PLUS 69
# define KEYPAD_MINUS 78
# define KEYPAD_DOT 65

# define MOUSE_WHEEL_UP 4
# define MOUSE_WHEEL_DOWN 5
# define MOUSE_LEFT_CLICK 1
# define MOUSE_RIGHT_CLICK 2

#endif
