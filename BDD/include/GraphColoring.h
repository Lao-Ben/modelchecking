//
//  GraphColoring.h
//  BDD2
//
//  Created by Benjamin Lefebvre on 29/03/13.
//  Copyright (c) 2013 Benjamin Lefebvre. All rights reserved.
//

#ifndef __BDD2__GraphColoring__
#define __BDD2__GraphColoring__

#include <iostream>
#include "BDD.h"

class GraphColoring {

public:
  static const int vertex = 4;

//  const std::string formula ="\
( Ral xor Gal xor Bal xor Yal ) \
&& ( Rfl xor Gfl xor Bfl xor Yfl ) \
&& ( Rga xor Gga xor Bga xor Yga ) \
&& ( Rms xor Gms xor Bms xor Yms ) \
&& ( Rtn xor Gtn xor Btn xor Ytn ) \
 \
&& ( ! ( ( Ral && Rfl ) || ( Gal && Gfl ) || ( Bal && Bfl ) || ( Yal && Yfl ) ) ) \
&& ( ! ( ( Ral && Rga ) || ( Gal && Gga ) || ( Bal && Bga ) || ( Yal && Yga ) ) ) \
&& ( ! ( ( Ral && Rms ) || ( Gal && Gms ) || ( Bal && Bms ) || ( Yal && Yms ) ) ) \
&& ( ! ( ( Ral && Rtn ) || ( Gal && Gtn ) || ( Bal && Btn ) || ( Yal && Ytn ) ) ) \
\
&& ( ! ( ( Rfl && Rga ) || ( Gfl && Gga ) || ( Bfl && Bga ) || ( Yfl && Yga ) ) ) \
";

  //GraphColoring();

  int compute();
  void toFile(std::string filename);
};


#endif /* defined(__BDD2__GraphColoring__) */
