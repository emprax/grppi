/**
* @version		GrPPI v0.2
* @copyright		Copyright (C) 2017 Universidad Carlos III de Madrid. All rights reserved.
* @license		GNU/GPL, see LICENSE.txt
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You have received a copy of the GNU General Public License in LICENSE.txt
* also available in <http://www.gnu.org/licenses/gpl.html>.
*
* See COPYRIGHT.txt for copyright notices and details.
*/

#ifndef GRPPI_MAP_SEQ_H
#define GRPPI_MAP_SEQ_H

namespace grppi{

template <typename InputIt, typename OutputIt, typename TaskFunc>
 void map(sequential_execution s, InputIt first, InputIt last, OutputIt firstOut, TaskFunc && taskf ) {
    while( first != last ) {
       *firstOut = taskf(*first);
       first++;
       firstOut++;
    }
}

template <typename InputIt, typename OutputIt, typename ... MoreIn, typename TaskFunc>
 void map(sequential_execution s, InputIt first, InputIt last, OutputIt firstOut, TaskFunc && taskf, MoreIn ... inputs ) {
    while( first != last ) {
        *firstOut = taskf( *first, *inputs ... );
        advance_iterators( inputs... );
        first++;
        firstOut++;
    }
}
}
#endif
