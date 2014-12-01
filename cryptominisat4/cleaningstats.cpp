/*
 * CryptoMiniSat
 *
 * Copyright (c) 2009-2014, Mate Soos. All rights reserved.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation
 * version 2.0 of the License.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301  USA
*/

#include "cleaningstats.h"
#include "solvertypes.h"

using namespace CMSat;

#include <iostream>
#include "solver.h"
using std::cout;
using std::endl;

void CleaningStats::print(const size_t nbReduceDB) const
{
    cout << "c ------ CLEANING STATS ---------" << endl;

    //-->CLEAN
    print_stats_line("c cleaned cls"
        , removed.num
        , stats_line_percent(removed.num, origNumClauses)
        , "% long redundant clauses"
    );
    print_stats_line("c cleaned lits"
        , removed.lits
        , stats_line_percent(removed.lits, origNumLits)
        , "% long red lits"
    );
    print_stats_line("c cleaned cl avg size"
        , (double)removed.lits/(double)removed.num
    );
    print_stats_line("c cleaned avg glue"
        , (double)removed.glue/(double)removed.num
    );

    //--> REMAIN
    print_stats_line("c remain cls"
        , remain.num
        , stats_line_percent(remain.num, origNumClauses)
        , "% long redundant clauses"
    );
    print_stats_line("c remain lits"
        , remain.lits
        , stats_line_percent(remain.lits, origNumLits)
        , "% long red lits"
    );
    print_stats_line("c remain cl avg size"
        , (double)remain.lits/(double)remain.num
    );
    print_stats_line("c remain avg glue"
        , (double)remain.glue/(double)remain.num
    );

    cout << "c ------ CLEANING STATS END ---------" << endl;
}

void CleaningStats::print_short(const Solver* solver) const
{
    cout
    << "c [DBclean]"
    << " removed " << removed.num

    << " avgGlue " << std::fixed << std::setprecision(2)
    << ((double)removed.glue/(double)removed.num)

    << " avgSize "
    << std::fixed << std::setprecision(2)
    << ((double)removed.lits/(double)removed.num)
    << endl;

    cout
    << "c [DBclean]"
    << " remain " << remain.num

    << " avgGlue " << std::fixed << std::setprecision(2)
    << ((double)remain.glue/(double)remain.num)

    << " avgSize " << std::fixed << std::setprecision(2)
    << ((double)remain.lits/(double)remain.num)

    << solver->conf.print_times(cpu_time)
    << endl;
}

CleaningStats& CleaningStats::operator+=(const CleaningStats& other)
{
    //Time
    cpu_time += other.cpu_time;

    //Before remove
    origNumClauses += other.origNumClauses;
    origNumLits += other.origNumLits;

    //Clause Cleaning data
    removed += other.removed;
    remain += other.remain;

    return *this;
}
