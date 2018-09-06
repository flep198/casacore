//# tTableGramFunc.cc: This program tests TaQL functions
//# Copyright (C) 2018
//# Associated Universities, Inc. Washington DC, USA.
//#
//# This program is free software; you can redistribute it and/or modify it
//# under the terms of the GNU General Public License as published by the Free
//# Software Foundation; either version 2 of the License, or (at your option)
//# any later version.
//#
//# This program is distributed in the hope that it will be useful, but WITHOUT
//# ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
//# FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
//# more details.
//#
//# You should have received a copy of the GNU General Public License along
//# with this program; if not, write to the Free Software Foundation, Inc.,
//# 675 Massachusetts Ave, Cambridge, MA 02139, USA.
//#
//# Correspondence concerning AIPS++ should be addressed as follows:
//#        Internet email: aips2-request@nrao.edu.
//#        Postal address: AIPS++ Project Office
//#                        National Radio Astronomy Observatory
//#                        520 Edgemont Road
//#                        Charlottesville, VA 22903-2475 USA
//#
//# $Id$

#include <casacore/tables/TaQL/TableParse.h>
#include <casacore/casa/Arrays/ArrayLogical.h>
#include <casacore/casa/BasicSL/Complex.h>
#include <casacore/casa/BasicSL/Constants.h>
#include <casacore/casa/Exceptions/Error.h>
#include <casacore/casa/iostream.h>

#include <casacore/casa/namespace.h>

// <summary>
// Test program for all TaQL functions
// </summary>

int ntest=0;


int checkScaBool (const String& func, const String& arg, Bool expResult)
{
  ntest++;
  String comm = "using style python calc " + func + '(' + arg + ')';
  try {
    TaQLResult result = tableCommand (comm);
    TableExprNode node = result.node();
    if (node.getBool(0) != expResult  ||  node.unit().getName() != "") {
      cout << "Bool error in evaluating: " + comm << endl;
      cout << " expected " << expResult << endl;
      cout << " found    " << node.getBool(0) << ' '
           << node.unit().getName() << endl;
      return 1;
    }
  } catch (const AipsError& x) {
    cout << x.getMesg() << endl;
    cout << "    Unexpected exception in: " << comm << endl;
    return 1;
  }
  return 0;
}

int checkScaInt (const String& func, const String& arg, Int expResult)
{
  ntest++;
  String comm = "using style python calc " + func + '(' + arg + ')';
  try {
    TaQLResult result = tableCommand (comm);
    TableExprNode node = result.node();
    if (node.getInt(0) != expResult  ||  node.unit().getName() != "") {
      cout << "Int error in evaluating: " + comm << endl;
      cout << " expected " << expResult << endl;
      cout << " found    " << node.getInt(0) << ' '
           << node.unit().getName() << endl;
      return 1;
    }
  } catch (const AipsError& x) {
    cout << x.getMesg() << endl;
    cout << "    Unexpected exception in: " << comm << endl;
    return 1;
  }
  return 0;
}

int checkScaDouble (const String& func, const String& arg, Double expResult,
                    const String& unit = String())
{
  ntest++;
  String comm = "using style python calc " + func + '(' + arg + ')';
  try {
    TaQLResult result = tableCommand (comm);
    TableExprNode node = result.node();
    if (!near(node.getDouble(0), expResult)  ||  node.unit().getName() != unit) {
      cout << "Double error in evaluating: " + comm << endl;
      cout << " expected " << expResult << endl;
      cout << " found    " << node.getDouble(0) << ' '
           << node.unit().getName() << endl;
      return 1;
    }
  } catch (const AipsError& x) {
    cout << x.getMesg() << endl;
    cout << "    Unexpected exception in: " << comm << endl;
    return 1;
  }
  return 0;
}

int checkScaDComplex (const String& func, const String& arg, DComplex expResult)
{
  ntest++;
  String comm = "using style python calc " + func + '(' + arg + ')';
  try {
    TaQLResult result = tableCommand (comm);
    TableExprNode node = result.node();
    if (!near(node.getDComplex(0), expResult)  ||  node.unit().getName() != "") {
      cout << "DComplex error in evaluating: " + comm << endl;
      cout << " expected " << expResult << endl;
      cout << " found    " << node.getDComplex(0) << ' '
           << node.unit().getName() << endl;
      return 1;
    }
  } catch (const AipsError& x) {
    cout << x.getMesg() << endl;
    cout << "    Unexpected exception in: " << comm << endl;
    return 1;
  }
  return 0;
}

int checkScaString (const String& func, const String& arg, String expResult)
{
  ntest++;
  String comm = "using style python calc " + func + '(' + arg + ')';
  try {
    TaQLResult result = tableCommand (comm);
    TableExprNode node = result.node();
    if (node.getString(0) != expResult  ||  node.unit().getName() != "") {
      cout << "String error in evaluating: " + comm << endl;
      cout << " expected " << expResult << endl;
      cout << " found    " << node.getString(0) << ' '
           << node.unit().getName() << endl;
      return 1;
    }
  } catch (const AipsError& x) {
    cout << x.getMesg() << endl;
    cout << "    Unexpected exception in: " << comm << endl;
    return 1;
  }
  return 0;
}

int checkArrBool (const String& func, const String& arg, const String& expResult)
{
  ntest++;
  String comm1 = "using style python calc " + func + '(' + arg + ')';
  String comm2 = "using style python calc " + expResult;
  try {
    TaQLResult result1 = tableCommand (comm1);
    TableExprNode node1 = result1.node();
    TaQLResult result2 = tableCommand (comm2);
    TableExprNode node2 = result2.node();
    if (! allEQ (node1.getArrayBool(0), node2.getArrayBool(0))) {
      cout << "Bool Array error in evaluating: " + comm1 << endl;
      cout << " expected " << node2.getArrayBool(0) << endl;
      cout << " found    " << node1.getArrayBool(0) << endl;
      return 1;
    }
  } catch (const AipsError& x) {
    cout << x.getMesg() << endl;
    cout << "    Unexpected exception in: " << comm1 << endl;
    return 1;
  }
  return 0;
}

int checkArrInt (const String& func, const String& arg, const String& expResult)
{
  ntest++;
  String comm1 = "using style python calc " + func + '(' + arg + ')';
  String comm2 = "using style python calc " + expResult;
  try {
    TaQLResult result1 = tableCommand (comm1);
    TableExprNode node1 = result1.node();
    TaQLResult result2 = tableCommand (comm2);
    TableExprNode node2 = result2.node();
    if (! allEQ (node1.getArrayInt(0), node2.getArrayInt(0))) {
      cout << "Int Array error in evaluating: " + comm1 << endl;
      cout << " expected " << node2.getArrayInt(0) << endl;
      cout << " found    " << node1.getArrayInt(0) << endl;
      return 1;
    }
  } catch (const AipsError& x) {
    cout << x.getMesg() << endl;
    cout << "    Unexpected exception in: " << comm1 << endl;
    return 1;
  }
  return 0;
}

int checkArrDouble (const String& func, const String& arg, const String& expResult)
{
  ntest++;
  String comm1 = "using style python calc " + func + '(' + arg + ')';
  String comm2 = "using style python calc " + expResult;
  try {
    TaQLResult result1 = tableCommand (comm1);
    TableExprNode node1 = result1.node();
    TaQLResult result2 = tableCommand (comm2);
    TableExprNode node2 = result2.node();
    if (! allNear (node1.getArrayDouble(0), node2.getArrayDouble(0), 1e-10)) {
      cout << "Double Array error in evaluating: " + comm1 << endl;
      cout << " expected " << node2.getArrayDouble(0) << endl;
      cout << " found    " << node1.getArrayDouble(0) << endl;
      return 1;
    }
  } catch (const AipsError& x) {
    cout << x.getMesg() << endl;
    cout << "    Unexpected exception in: " << comm1 << endl;
    return 1;
  }
  return 0;
}

int checkArrDComplex (const String& func, const String& arg, const String& expResult)
{
  ntest++;
  String comm1 = "using style python calc " + func + '(' + arg + ')';
  String comm2 = "using style python calc " + expResult;
  try {
    TaQLResult result1 = tableCommand (comm1);
    TableExprNode node1 = result1.node();
    TaQLResult result2 = tableCommand (comm2);
    TableExprNode node2 = result2.node();
    if (! allNear (node1.getArrayDComplex(0), node2.getArrayDComplex(0), 1e-10)) {
      cout << "DComplex Array error in evaluating: " + comm1 << endl;
      cout << " expected " << node2.getArrayDComplex(0) << endl;
      cout << " found    " << node1.getArrayDComplex(0) << endl;
      return 1;
    }
  } catch (const AipsError& x) {
    cout << x.getMesg() << endl;
    cout << "    Unexpected exception in: " << comm1 << endl;
    return 1;
  }
  return 0;
}

int checkArrString (const String& func, const String& arg, const String& expResult)
{
  ntest++;
  String comm1 = "using style python calc " + func + '(' + arg + ')';
  String comm2 = "using style python calc " + expResult;
  try {
    TaQLResult result1 = tableCommand (comm1);
    TableExprNode node1 = result1.node();
    TaQLResult result2 = tableCommand (comm2);
    TableExprNode node2 = result2.node();
    if (! allEQ (node1.getArrayString(0), node2.getArrayString(0))) {
      cout << "String Array error in evaluating: " + comm1 << endl;
      cout << " expected " << node2.getArrayString(0) << endl;
      cout << " found    " << node1.getArrayString(0) << endl;
      return 1;
    }
  } catch (const AipsError& x) {
    cout << x.getMesg() << endl;
    cout << "    Unexpected exception in: " << comm1 << endl;
    return 1;
  }
  return 0;
}

int checkExcp (const String& func, const String& arg,
               const String& msgPart=String())
{
  ntest++;
  String comm = "using style python calc " + func + '(' + arg + ')';
  try {
    tableCommand (comm);
  } catch (const AipsError& x) {
    if (msgPart.empty()) {
      cout << x.getMesg() << endl;
    } else if (x.getMesg().find (msgPart) == String::npos) {
      cout << x.getMesg() << endl;
      cout << "    Expected another exception in: " << comm << endl;
      return 1;
    }
    return 0;
  }
  cout << "Expected exception in: " << comm << endl;
  return 1;
}


int testScaBool()
{
  cout<<"  testing scalar Bool functions ..."<<endl;
  int nfail = 0;
  nfail += checkScaBool ("near", "2., 2.0000001, 1e-5", True);
  nfail += checkScaBool ("near", "2., 2.0000001", False);
  nfail += checkScaBool ("near", "2+3i, 2.0000001+3i", False);
  nfail += checkScaBool ("near", "2+3i, 2+3.0000001i", False);
  nfail += checkScaBool ("near", "2+3i, 2.0000001+3.0000001i, 1e-5", True);
  nfail += checkScaBool ("near", "2, 2+3i", False);
  nfail += checkScaBool ("nearAbs", "2, 3", False);
  nfail += checkScaBool ("nearAbs", "2, 3, 2", True);
  nfail += checkScaBool ("nearAbs", "2+3i, 2.0000001+3.0000001i", False);
  nfail += checkScaBool ("nearAbs", "2+3i, 2.0000001+3.0000001i, 1e-5", True);
  nfail += checkScaBool ("isnan", "2", False);
  nfail += checkScaBool ("isnan", "0/0", True);
  nfail += checkScaBool ("isinf", "2", False);
  nfail += checkScaBool ("isinf", "2/0", True);
  nfail += checkScaBool ("isfinite", "2", True);
  nfail += checkScaBool ("isnan", "2.", False);
  nfail += checkScaBool ("isinf", "2.", False);
  nfail += checkScaBool ("isfinite", "2.", True);
  nfail += checkScaBool ("isfinite", "2./0", False);
  nfail += checkScaBool ("isnan", "2i", False);
  nfail += checkScaBool ("isinf", "2i", False);
  nfail += checkScaBool ("isfinite", "2j", True);
  nfail += checkScaBool ("isfinite", "0j/0", False);
  nfail += checkScaBool ("isnull", "nullarray(1)", True);
  nfail += checkScaBool ("isnull", "array(1, [0])", False);
  return nfail;
}

int testScaInt()
{
  cout<<"  testing scalar Int functions ..."<<endl;
  int nfail = 0;
  nfail += checkScaInt ("sqr", "4", 16);
  nfail += checkScaInt ("cube", "4", 64);
  nfail += checkScaInt ("min", "-1,3", -1);
  nfail += checkScaInt ("max", "-6, -4", -4);
  nfail += checkScaInt ("norm", "-6", 36);
  nfail += checkScaInt ("abs", "-6", 6);
  nfail += checkScaInt ("int", "F", 0);
  nfail += checkScaInt ("int", "T", 1);
  nfail += checkScaInt ("int", "2", 2);
  nfail += checkScaInt ("int", "2.5", 2);
  nfail += checkScaInt ("integer", "'-3.7'", -3);
  nfail += checkScaInt ("sign", "-3", -1);
  nfail += checkScaInt ("sign", "0", 0);
  nfail += checkScaInt ("sign", "3", 1);
  nfail += checkScaInt ("round", "3", 3);
  nfail += checkScaInt ("round", "-3", -3);
  nfail += checkScaInt ("floor", "3", 3);
  nfail += checkScaInt ("ceil", "3", 3);
  nfail += checkScaInt ("fmod", "8,3", 2);
  nfail += checkScaInt ("fmod", "-8,3", -2);
  nfail += checkScaInt ("fmod", "8,-3", 2);
  nfail += checkScaInt ("fmod", "-8,-3", -2);
  return nfail;
}

int testScaDouble()
{
  cout<<"  testing scalar Double functions ..."<<endl;
  int nfail = 0;
  nfail += checkScaDouble ("pi", "", C::pi);
  nfail += checkScaDouble ("e", "", C::e);
  nfail += checkScaDouble ("c", "", C::c, "m/s");
  nfail += checkScaDouble ("sin", "0.5", sin(0.5));
  nfail += checkScaDouble ("sinh", "2", sinh(2));
  nfail += checkScaDouble ("cos", "0.6", cos(0.6));
  nfail += checkScaDouble ("cosh", "1.5", cosh(1.5));
  nfail += checkScaDouble ("exp", "0.5", sqrt(C::e));
  nfail += checkScaDouble ("log", "e()*e()", 2.);
  nfail += checkScaDouble ("log10", "0.1", -1.);
  nfail += checkScaDouble ("sqrt", "4", 2.);
  nfail += checkScaDouble ("sqrt", "4.", 2.);
  nfail += checkScaDouble ("pow", "1.6, 1.5", 1.6*sqrt(1.6));
  nfail += checkScaDouble ("conj", "0.1", 0.1);
  nfail += checkScaDouble ("square", "-4.5", 4.5*4.5);
  nfail += checkScaDouble ("cube", "-1.4", -1.4*1.4*1.4);
  nfail += checkScaDouble ("min", "-1.4,-5", -5.);
  nfail += checkScaDouble ("max", "1,2.", 2.);
  nfail += checkScaDouble ("max", "1,2", 2.);     // also works for all integer
  nfail += checkScaDouble ("norm", "-6.1", 6.1*6.1);
  nfail += checkScaDouble ("abs", "-6.5", 6.5);
  nfail += checkScaDouble ("arg", "6", 0., "rad");
  nfail += checkScaDouble ("arg", "-6", C::pi, "rad");
  nfail += checkScaDouble ("real", "F", 0.);
  nfail += checkScaDouble ("real", "T", 1.);
  nfail += checkScaDouble ("real", "2", 2.);
  nfail += checkScaDouble ("real", "2.5", 2.5);
  nfail += checkScaDouble ("real", "'-2.7-1i'", -2.7);
  nfail += checkScaDouble ("real", "'-3.7'", -3.7);
  nfail += checkScaDouble ("imag", "2", 0.);
  nfail += checkScaDouble ("imag", "2.5", 0);
  nfail += checkScaDouble ("imag", "-2.7-1i", -1.);
  nfail += checkScaDouble ("asin", "0.5", asin(0.5), "rad");
  nfail += checkScaDouble ("acos", "0.65", acos(0.65), "rad");
  nfail += checkScaDouble ("atan", "0.3", atan(0.3), "rad");
  nfail += checkScaDouble ("atan2", "0.5,0.3", atan2(0.5,0.3), "rad");
  nfail += checkScaDouble ("tan", "1.2", tan(1.2));
  nfail += checkScaDouble ("tanh", "-1.2", tanh(-1.2));
  nfail += checkScaDouble ("sign", "-3", -1);
  nfail += checkScaDouble ("sign", "0", 0);
  nfail += checkScaDouble ("sign", "3", 1);
  nfail += checkScaDouble ("round", "3.1", 3);
  nfail += checkScaDouble ("round", "3.5", 4);
  nfail += checkScaDouble ("round", "-3.1", -3);
  nfail += checkScaDouble ("round", "-3.5", -4);
  nfail += checkScaDouble ("floor", "3.1", 3);
  nfail += checkScaDouble ("floor", "-3.1", -4);
  nfail += checkScaDouble ("ceil", "3.1", 4);
  nfail += checkScaDouble ("ceil", "-3.1", -3);
  nfail += checkScaDouble ("fmod", "8.1,3.2", 1.7);
  nfail += checkScaDouble ("fmod", "-8.1,3.2", -1.7);
  nfail += checkScaDouble ("fmod", "8.1,-3.2", 1.7);
  nfail += checkScaDouble ("fmod", "-8.1,-3.2", -1.7);
  return nfail;
}

int testScaDComplex()
{
  cout<<"  testing scalar DComplex functions ..."<<endl;
  int nfail = 0;
  nfail += checkScaDComplex ("sin", "0.5+0.6i", sin(DComplex(0.5,0.6)));
  nfail += checkScaDComplex ("sinh", "2+2.1i", sinh(DComplex(2,2.1)));
  nfail += checkScaDComplex ("cos", "0.6+0.4i", cos(DComplex(0.6,0.4)));
  nfail += checkScaDComplex ("cosh", "1.5+0.6i", cosh(DComplex(1.5,0.6)));
  nfail += checkScaDComplex ("exp", "0.5+2i", exp(DComplex(0.5,2)));
  nfail += checkScaDComplex ("log", "1+3i", log(DComplex(1,3)));
  nfail += checkScaDComplex ("log10", "0.1-3i", log10(DComplex(0.1,-3)));
  nfail += checkScaDComplex ("sqrt", "4", DComplex(2,0));
  nfail += checkScaDComplex ("sqrt", "4.", DComplex(2,0));
  nfail += checkScaDComplex ("sqrt", "8i", DComplex(2,2));
  nfail += checkScaDComplex ("pow", "1.6+2i, 1.5", DComplex(1.6,2)*sqrt(DComplex(1.6,2)));
  nfail += checkScaDComplex ("conj", "1+2i", DComplex(1,-2));
  nfail += checkScaDComplex ("sqr", "-4.5+3i", DComplex(-4.5,3) * DComplex(-4.5,3));
  nfail += checkScaDComplex ("sqr", "-4.5", DComplex(4.5*4.5, 0));
  nfail += checkScaDComplex ("cube", "1.4+1i", DComplex(1.4,1)*DComplex(1.4,1)*DComplex(1.4,1));
  nfail += checkScaDComplex ("min", "-1.4+1i, -5+8i", DComplex(-1.4,1));
  nfail += checkScaDComplex ("max", "-1.4+1i, -5+8i", DComplex(-5,8));
  nfail += checkScaDComplex ("complex", "-1.4,1", DComplex(-1.4,1));
  nfail += checkScaDComplex ("complex", "'-1.4+10j'", DComplex(-1.4,10));
  nfail += checkScaDComplex ("complex", "'-1.4'", DComplex(-1.4,0));
  return nfail;
}

int testScaString()
{
  cout<<"  testing scalar String functions ..."<<endl;
  int nfail = 0;
  return nfail;
}

int testRegex()
{
  cout<<"  testing Regex functions ..."<<endl;
  int nfail = 0;
  return nfail;
}

int testArrBool()
{
  cout<<"  testing array Bool functions ..."<<endl;
  int nfail = 0;
  return nfail;
}

int testArrInt()
{
  cout<<"  testing array Int functions ..."<<endl;
  int nfail = 0;
  nfail += checkArrInt ("array", "[[1,2,3]], 2,3", "[[1,2,3],[1,2,3]]");
  nfail += checkArrInt ("array", "[[1,2,3]], 1,3,2", "[[[1,2],[3,1],[2,3]]]");
  nfail += checkArrInt ("transpose", "[[1,2,3],[4,5,6],[7,8,9]]", "[[1,4,7],[2,5,8],[3,6,9]]");
  nfail += checkArrInt ("transpose", "[[[1,2],[4,5],[7,8]]], [2,0]",
                        "[[[1,4,7]],[[2,5,8]]]");      // axes get 2,0,1 -> shape 3,1,2
  nfail += checkArrInt ("resize", "[[1,2,3],[4,5,6]], [3,2]", "[[1,2],[4,5],[0,0]]");
  nfail += checkArrInt ("resize", "[[1,2,3],[4,5,6]], [2,6], 0", "[[1,1,2,2,3,3],[4,4,5,5,6,6]]");
  nfail += checkArrInt ("resize", "[[1,2,3],[4,5,6]], [2,6], 1", "[[1,2,3,1,2,3],[4,5,6,4,5,6]]");
  nfail += checkArrInt ("sums", "[[1,2,3],[4,5,6]], 1", "[6,15]");
  nfail += checkArrInt ("sums", "[[1,2,3],[4,5,6]], 0", "[5,7,9]");
  nfail += checkArrInt ("products", "[[1,2,3],[4,5,6]], 0", "[4,10,18]");
  nfail += checkArrInt ("sumsqrs", "[[1,2,3],[4,5,6]], 0", "[17,29,45]");
  nfail += checkArrInt ("mins", "[[[1,2,3],[4,5,6]]], 1", "[[1,2,3]]");
  nfail += checkArrInt ("maxs", "[[[1,2,3],[4,5,6]]], 0", "[[1,2,3],[4,5,6]]");
  return nfail;
}

int testArrDouble()
{
  cout<<"  testing array Double functions ..."<<endl;
  int nfail = 0;
  nfail += checkArrDouble ("sums", "[[1.1,2,3],[4,5,6]], 1", "[6.1,15]");
  nfail += checkArrDouble ("sums", "[[1.1,2,3],[4,5,6]], 0", "[5.1,7,9]");
  nfail += checkArrDouble ("products", "[[1,2,3],[4,5.,6]], 0", "[4,10,18]");
  nfail += checkArrDouble ("sumsqrs", "[[1,2,3],[4,5,6.]], 0", "[17,29,45]");
  nfail += checkArrDouble ("mins", "[[[1,2,3],[4,5,6.]]], 1", "[[1,2,3]]");
  nfail += checkArrDouble ("maxs", "[[[1,2,3],[4,5,6.]]], 0", "[[1,2,3],[4,5,6]]");
  nfail += checkArrDouble ("means", "[[1,2,3],[4,5,6.]], 0", "[2.5,3.5,4.5]");
  nfail += checkArrDouble ("variances", "[[1,2,3],[4,5,7.]], 1", "[1,7./3]");
  nfail += checkArrDouble ("stddevs", "[[1,2,3],[4,5,7.]], 1", "[1,sqrt(7./3)]");
  nfail += checkArrDouble ("avdevs", "[[1,2,3],[4,5,7.]], 0", "[1.5,1.5,2]");
  nfail += checkArrDouble ("rmss", "[[1,2,3],[4,5,7.]], 1", "[sqrt(14./3), sqrt(90./3)]");
  nfail += checkArrDouble ("medians", "[[1,2,3],[4,5,6.]], 1", "[2,5]");
  nfail += checkArrDouble ("fractiles", "[[1,2,3],[4,5,6.]], 0.5, [1]", "[2,5]");
  nfail += checkArrDouble ("boxedsum", "[[1.1,2,3],[4,5,6]], [2,2]", "[[12.1,9]]");
  return nfail;
}

int testArrDComplex()
{
  cout<<"  testing array DComplex functions ..."<<endl;
  int nfail = 0;
  return nfail;
}

int testArrString()
{
  cout<<"  testing array String functions ..."<<endl;
  int nfail = 0;
  return nfail;
}

int testLessArg()
{
  cout<<"  testing functions with too few arguments ..."<<endl;
  int nfail = 0;
  nfail += checkExcp ("NEAR", "1", "- too few ");
  nfail += checkExcp ("NearAbs", "", "- too few ");
  nfail += checkExcp ("sin", "", "- too few ");
  nfail += checkExcp ("sinh", "", "- too few ");
  nfail += checkExcp ("cos", "", "- too few ");
  nfail += checkExcp ("cosh", "", "- too few ");
  nfail += checkExcp ("exp", "", "- too few ");
  nfail += checkExcp ("log", "", "- too few ");
  nfail += checkExcp ("log10", "", "- too few ");
  nfail += checkExcp ("sqrt", "", "- too few ");
  nfail += checkExcp ("pow", "2", "- too few ");
  nfail += checkExcp ("conj", "", "- too few ");
  nfail += checkExcp ("sqr", "", "- too few ");
  nfail += checkExcp ("cube", "", "- too few ");
  nfail += checkExcp ("min", "", "- too few ");
  nfail += checkExcp ("max", "", "- too few ");
  nfail += checkExcp ("norm", "", "- too few ");
  nfail += checkExcp ("abs", "", "- too few ");
  nfail += checkExcp ("arg", "", "- too few ");
  nfail += checkExcp ("real", "", "- too few ");
  nfail += checkExcp ("imag", "", "- too few ");
  nfail += checkExcp ("int", "", "- too few ");
  nfail += checkExcp ("sign", "", "- too few ");
  nfail += checkExcp ("round", "", "- too few ");
  nfail += checkExcp ("ceil", "", "- too few ");
  nfail += checkExcp ("floor", "", "- too few ");
  nfail += checkExcp ("fmod", "", "- too few ");
  nfail += checkExcp ("complex", "-1.4", "- too few ");
  nfail += checkExcp ("array", "1", "- too few ");
  nfail += checkExcp ("transpose", "", "- too few ");
  nfail += checkExcp ("diagonal", "", "- too few ");
  nfail += checkExcp ("resize", "1", "- too few ");
  nfail += checkExcp ("sums", "1", "- too few ");
  nfail += checkExcp ("products", "1", "- too few ");
  nfail += checkExcp ("sumsqrs", "1", "- too few ");
  nfail += checkExcp ("mins", "1", "- too few ");
  nfail += checkExcp ("maxs", "1", "- too few ");
  nfail += checkExcp ("means", "1", "- too few ");
  nfail += checkExcp ("variances", "1", "- too few ");
  nfail += checkExcp ("stddevs", "1", "- too few ");
  nfail += checkExcp ("avdevs", "1", "- too few ");
  nfail += checkExcp ("rmss", "1", "- too few ");
  nfail += checkExcp ("medians", "1", "- too few ");
  nfail += checkExcp ("fractiles", "1,0.5", "- too few ");
  nfail += checkExcp ("alls", "1", "- too few ");
  nfail += checkExcp ("anys", "1", "- too few ");
  nfail += checkExcp ("ntrues", "1", "- too few ");
  nfail += checkExcp ("nfalses", "1", "- too few ");
  nfail += checkExcp ("runningsum", "1", "- too few ");
  nfail += checkExcp ("runningproduct", "1", "- too few ");
  nfail += checkExcp ("runningsumsqr", "1", "- too few ");
  nfail += checkExcp ("runningmin", "1", "- too few ");
  nfail += checkExcp ("runningmax", "1", "- too few ");
  nfail += checkExcp ("runningmean", "1", "- too few ");
  nfail += checkExcp ("runningvariance", "1", "- too few ");
  nfail += checkExcp ("runningstddev", "1", "- too few ");
  nfail += checkExcp ("runningavdev", "1", "- too few ");
  nfail += checkExcp ("runningrms", "1", "- too few ");
  nfail += checkExcp ("runningmedian", "1", "- too few ");
  nfail += checkExcp ("runningfractile", "1,0.5", "- too few ");
  nfail += checkExcp ("runningall", "1", "- too few ");
  nfail += checkExcp ("runningany", "1", "- too few ");
  nfail += checkExcp ("runningntrue", "1", "- too few ");
  nfail += checkExcp ("runningnfalse", "1", "- too few ");
  nfail += checkExcp ("boxedsum", "1", "- too few ");
  nfail += checkExcp ("boxedproduct", "1", "- too few ");
  nfail += checkExcp ("boxedsumsqr", "1", "- too few ");
  nfail += checkExcp ("boxedmin", "1", "- too few ");
  nfail += checkExcp ("boxedmax", "1", "- too few ");
  nfail += checkExcp ("boxedmean", "1", "- too few ");
  nfail += checkExcp ("boxedvariance", "1", "- too few ");
  nfail += checkExcp ("boxedstddev", "1", "- too few ");
  nfail += checkExcp ("boxedavdev", "1", "- too few ");
  nfail += checkExcp ("boxedrms", "1", "- too few ");
  nfail += checkExcp ("boxedmedian", "1", "- too few ");
  nfail += checkExcp ("boxedfractile", "1,0.5", "- too few ");
  nfail += checkExcp ("boxedall", "1", "- too few ");
  nfail += checkExcp ("boxedany", "1", "- too few ");
  nfail += checkExcp ("boxedntrue", "1", "- too few ");
  nfail += checkExcp ("boxednfalse", "1", "- too few ");
  nfail += checkExcp ("isnan", "", "- too few ");
  nfail += checkExcp ("isinf", "", "- too few ");
  nfail += checkExcp ("isfinite", "", "- too few ");
  return nfail;
}

int testMoreArg()
{
  cout<<"  testing functions with too many arguments ..."<<endl;
  int nfail = 0;
  nfail += checkExcp ("pi", "1", "- too many ");
  nfail += checkExcp ("e", "1", "- too many ");
  nfail += checkExcp ("c", "1", "- too many ");
  nfail += checkExcp ("NEAR", "1,2,3,4", "- too many ");
  nfail += checkExcp ("NearAbs", "1,2,3,4", "- too many ");
  nfail += checkExcp ("sin", "1,2", "- too many ");
  nfail += checkExcp ("sinh", "2,3", "- too many ");
  nfail += checkExcp ("cos", "3,4", "- too many ");
  nfail += checkExcp ("cosh", "4,5", "- too many ");
  nfail += checkExcp ("exp", "1,2", "- too many ");
  nfail += checkExcp ("log", "1,2", "- too many ");
  nfail += checkExcp ("log10", "2,3", "- too many ");
  nfail += checkExcp ("sqrt", "1,2", "- too many ");
  nfail += checkExcp ("pow", "2,3,4", "- too many ");
  nfail += checkExcp ("conj", "2,4", "- too many ");
  nfail += checkExcp ("sqr", "2,4", "- too many ");
  nfail += checkExcp ("cube", "2,4", "- too many ");
  nfail += checkExcp ("min", "2,4,3", "- too many ");
  nfail += checkExcp ("max", "2,4,3", "- too many ");
  nfail += checkExcp ("norm", "2,4", "- too many ");
  nfail += checkExcp ("amplitude", "4,3", "- too many ");
  nfail += checkExcp ("phase", "2,3", "- too many ");
  nfail += checkExcp ("real", "2,4", "- too many ");
  nfail += checkExcp ("imag", "2,4", "- too many ");
  nfail += checkExcp ("integer", "2,3", "- too many ");
  nfail += checkExcp ("sign", "2,3", "- too many ");
  nfail += checkExcp ("round", "2,3", "- too many ");
  nfail += checkExcp ("ceil", "2,3", "- too many ");
  nfail += checkExcp ("floor", "2,3", "- too many ");
  nfail += checkExcp ("fmod", "2,3,4", "- too many ");
  nfail += checkExcp ("complex", "-1.4,4,5", "- too many ");
  nfail += checkExcp ("resize", "1,2,3,4", "- too many ");
  nfail += checkExcp ("isnan", "1,2", "- too many ");
  nfail += checkExcp ("isinf", "1,2", "- too many ");
  nfail += checkExcp ("isfinite", "1,2", "- too many ");
  return nfail;
}

int testInvScaArg()
{
  cout<<"  testing scalar functions with invalid arguments ..."<<endl;
  int nfail = 0;
  nfail += checkExcp ("near", "F,T", "- invalid operand data type");
  nfail += checkExcp ("near", "'4', '5'", "- invalid operand data type");
  nfail += checkExcp ("near", "date(), date()", "- invalid operand data type");
  nfail += checkExcp ("nearAbs", "True,False", "- invalid operand data type");
  nfail += checkExcp ("nearAbs", "'4', '5'", "- invalid operand data type");
  nfail += checkExcp ("nearAbs", "date(), date()", "- invalid operand data type");
  nfail += checkExcp ("sin", "T", "- invalid operand data type");
  nfail += checkExcp ("sin", "''", "- invalid operand data type");
  nfail += checkExcp ("sin", "date()", "- invalid operand data type");
  nfail += checkExcp ("sinh", "T", "- invalid operand data type");
  nfail += checkExcp ("sinh", "''", "- invalid operand data type");
  nfail += checkExcp ("sinh", "date()", "- invalid operand data type");
  nfail += checkExcp ("cos", "T", "- invalid operand data type");
  nfail += checkExcp ("cos", "''", "- invalid operand data type");
  nfail += checkExcp ("cos", "date()", "- invalid operand data type");
  nfail += checkExcp ("cosh", "T", "- invalid operand data type");
  nfail += checkExcp ("cosh", "''", "- invalid operand data type");
  nfail += checkExcp ("cosh", "date()", "- invalid operand data type");
  nfail += checkExcp ("exp", "F", "- invalid operand data type");
  nfail += checkExcp ("exp", "''", "- invalid operand data type");
  nfail += checkExcp ("exp", "date()", "- invalid operand data type");
  nfail += checkExcp ("log", "T", "- invalid operand data type");
  nfail += checkExcp ("log", "''", "- invalid operand data type");
  nfail += checkExcp ("log", "date()", "- invalid operand data type");
  nfail += checkExcp ("log10", "T", "- invalid operand data type");
  nfail += checkExcp ("log10", "''", "- invalid operand data type");
  nfail += checkExcp ("log10", "date()", "- invalid operand data type");
  nfail += checkExcp ("sqrt", "True", "- invalid operand data type");
  nfail += checkExcp ("sqrt", "'4'", "- invalid operand data type");
  nfail += checkExcp ("sqrt", "date()", "- invalid operand data type");
  nfail += checkExcp ("pow", "2,T", "- invalid operand data type");
  nfail += checkExcp ("pow", "T,2", "- invalid operand data type");
  nfail += checkExcp ("pow", "'',2", "- invalid operand data type");
  nfail += checkExcp ("pow", "2,''", "- invalid operand data type");
  nfail += checkExcp ("pow", "date(), 2", "- invalid operand data type");
  nfail += checkExcp ("conj", "T", "- invalid operand data type");
  nfail += checkExcp ("conj", "''", "- invalid operand data type");
  nfail += checkExcp ("conj", "date()", "- invalid operand data type");
  nfail += checkExcp ("sqr", "T", "- invalid operand data type");
  nfail += checkExcp ("sqr", "''", "- invalid operand data type");
  nfail += checkExcp ("sqr", "date()", "- invalid operand data type");
  nfail += checkExcp ("cube", "T", "- invalid operand data type");
  nfail += checkExcp ("cube", "''", "- invalid operand data type");
  nfail += checkExcp ("cube", "date()", "- invalid operand data type");
  nfail += checkExcp ("min", "T,F", "- invalid operand data type");
  nfail += checkExcp ("min", "'',3", "- invalid operand data type");
  nfail += checkExcp ("min", "date(),date()", "- invalid operand data type");
  nfail += checkExcp ("max", "4,T", "- invalid operand data type");
  nfail += checkExcp ("max", "'','a'", "- invalid operand data type");
  nfail += checkExcp ("max", "date(),date()", "- invalid operand data type");
  nfail += checkExcp ("norm", "T", "- invalid operand data type");
  nfail += checkExcp ("norm", "'2+3i'", "- invalid operand data type");
  nfail += checkExcp ("norm", "date()", "- invalid operand data type");
  nfail += checkExcp ("abs", "False", "- invalid operand data type");
  nfail += checkExcp ("abs", "'2+3i'", "- invalid operand data type");
  nfail += checkExcp ("abs", "date()", "- invalid operand data type");
  nfail += checkExcp ("arg", "F", "- invalid operand data type");
  nfail += checkExcp ("arg", "'2+3i'", "- invalid operand data type");
  nfail += checkExcp ("arg", "date()", "- invalid operand data type");
  nfail += checkExcp ("imag", "F", "- invalid operand data type");
  nfail += checkExcp ("imag", "'-3.7'", "- invalid operand data type");
  nfail += checkExcp ("imag", "date()", "- invalid operand data type");
  nfail += checkExcp ("int", "2+3i", "- invalid operand data type");
  nfail += checkExcp ("int", "date()", "- invalid operand data type");
  nfail += checkExcp ("isnan", "T", "- invalid operand data type");
  nfail += checkExcp ("isnan", "''", "- invalid operand data type");
  nfail += checkExcp ("isnan", "date()", "- invalid operand data type");
  nfail += checkExcp ("isinf", "T", "- invalid operand data type");
  nfail += checkExcp ("isinf", "''", "- invalid operand data type");
  nfail += checkExcp ("isinf", "date()", "- invalid operand data type");
  nfail += checkExcp ("isfinite", "T", "- invalid operand data type");
  nfail += checkExcp ("isfinite", "''", "- invalid operand data type");
  nfail += checkExcp ("isfinite", "date()", "- invalid operand data type");
  nfail += checkExcp ("isdefined", "COL", "Shorthand  has not been defined");
  nfail += checkExcp ("isnull", "COL", "Shorthand  has not been defined");
  nfail += checkExcp ("iscolumn", "COL", "Shorthand  has not been defined");
  nfail += checkExcp ("iskeyword", "COL", "Shorthand  has not been defined");
  return nfail;
}

int testNoArrArg()
{
  cout<<"  testing array functions with invalid arguments ..."<<endl;
  int nfail = 0;
  nfail += checkExcp ("transpose", "1,1", " has to be an array");
  nfail += checkExcp ("diagonal", "1,1", " has to be an array");
  nfail += checkExcp ("resize", "1,1", " has to be an array");
  nfail += checkExcp ("sums", "1,1", " has to be an array");
  nfail += checkExcp ("products", "1,1", " has to be an array");
  nfail += checkExcp ("sumsqrs", "1,1", " has to be an array");
  nfail += checkExcp ("mins", "1,1", " has to be an array");
  nfail += checkExcp ("maxs", "1,1", " has to be an array");
  nfail += checkExcp ("means", "1,1", " has to be an array");
  nfail += checkExcp ("variances", "1,1", " has to be an array");
  nfail += checkExcp ("stddevs", "1,1", " has to be an array");
  nfail += checkExcp ("avdevs", "1,1", " has to be an array");
  nfail += checkExcp ("rmss", "1,1", " has to be an array");
  nfail += checkExcp ("medians", "1,1", " has to be an array");
  nfail += checkExcp ("fractiles", "1,0.5,1", " has to be an array");
  nfail += checkExcp ("alls", "1,1", " has to be an array");
  nfail += checkExcp ("anys", "1,1", " has to be an array");
  nfail += checkExcp ("ntrues", "1,1", " has to be an array");
  nfail += checkExcp ("nfalses", "1,1", " has to be an array");
  nfail += checkExcp ("runningsum", "1,1", " has to be an array");
  nfail += checkExcp ("runningproduct", "1,1", " has to be an array");
  nfail += checkExcp ("runningsumsqr", "1,1", " has to be an array");
  nfail += checkExcp ("runningmin", "1,1", " has to be an array");
  nfail += checkExcp ("runningmax", "1,1", " has to be an array");
  nfail += checkExcp ("runningmean", "1,1", " has to be an array");
  nfail += checkExcp ("runningvariance", "1,1", " has to be an array");
  nfail += checkExcp ("runningstddev", "1,1", " has to be an array");
  nfail += checkExcp ("runningavdev", "1,1", " has to be an array");
  nfail += checkExcp ("runningrms", "1,1", " has to be an array");
  nfail += checkExcp ("runningmedian", "1,1", " has to be an array");
  nfail += checkExcp ("runningfractile", "1,0.5,1", " has to be an array");
  nfail += checkExcp ("runningall", "1,1", " has to be an array");
  nfail += checkExcp ("runningany", "1,1", " has to be an array");
  nfail += checkExcp ("runningntrue", "1,1", " has to be an array");
  nfail += checkExcp ("runningnfalse", "1,1", " has to be an array");
  nfail += checkExcp ("boxedsum", "1,1", " has to be an array");
  nfail += checkExcp ("boxedproduct", "1,1", " has to be an array");
  nfail += checkExcp ("boxedsumsqr", "1,1", " has to be an array");
  nfail += checkExcp ("boxedmin", "1,1", " has to be an array");
  nfail += checkExcp ("boxedmax", "1,1", " has to be an array");
  nfail += checkExcp ("boxedmean", "1,1", " has to be an array");
  nfail += checkExcp ("boxedvariance", "1,1", " has to be an array");
  nfail += checkExcp ("boxedstddev", "1,1", " has to be an array");
  nfail += checkExcp ("boxedavdev", "1,1", " has to be an array");
  nfail += checkExcp ("boxedrms", "1,1", " has to be an array");
  nfail += checkExcp ("boxedmedian", "1,1", " has to be an array");
  nfail += checkExcp ("boxedfractile", "1,0.5,1", " has to be an array");
  nfail += checkExcp ("boxedall", "1,1", " has to be an array");
  nfail += checkExcp ("boxedany", "1,1", " has to be an array");
  nfail += checkExcp ("boxedntrue", "1,1", " has to be an array");
  nfail += checkExcp ("boxednfalse", "1,1", " has to be an array");
  nfail += checkExcp ("array", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("transpose", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("diagonal", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("sums", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("products", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("sumsqrs", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("mins", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("maxs", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("means", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("variances", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("stddevs", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("avdevs", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("rmss", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("medians", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("fractiles", "1,0.5,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("alls", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("anys", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("ntrues", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("nfalses", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningsum", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningproduct", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningsumsqr", "1,[1],1", "are not one or more scalars or ");
  nfail += checkExcp ("runningmin", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningmax", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningmean", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningvariance", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningstddev", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningavdev", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningrms", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningmedian", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningfractile", "1,0.5,[1],1", "are not one or more scalars or ");
  nfail += checkExcp ("runningall", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningany", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningntrue", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("runningnfalse", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedsum", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedproduct", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedsumsqr", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedmin", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedmax", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedmean", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedvariance", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedstddev", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedavdev", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedrms", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedmedian", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedfractile", "1,0.5,[1],[2]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedall", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedany", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxedntrue", "1,1,[1]", "are not one or more scalars or ");
  nfail += checkExcp ("boxednfalse", "1,1,[1]", "are not one or more scalars or ");
  return nfail;
}

int main()
{
  int nfail = 0;
  try {
    nfail += testScaBool();
    nfail += testScaInt();
    nfail += testScaDouble();
    nfail += testScaDComplex();
    nfail += testScaString();
    nfail += testRegex();
    nfail += testArrBool();
    nfail += testArrInt();
    nfail += testArrDouble();
    nfail += testArrDComplex();
    nfail += testArrString();
    nfail += testLessArg();
    nfail += testMoreArg();
    nfail += testInvScaArg();
    nfail += testNoArrArg();
  } catch (const AipsError& x) {
    cout << "\nCaught an exception: " << x.getMesg() << endl;
    return 1;
  }
  cout << ntest << " tests done of which " << nfail << " failed" << endl;
  AlwaysAssertExit (nfail==0);
  return 0;               // successfully executed
}
