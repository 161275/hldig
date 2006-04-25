//
// TidyParser.h
//
// Part of the ht://Dig package   <http://www.htdig.org/>
// Copyright (c) 1995-2004 The ht://Dig Group
// For copyright details, see the file COPYING in your distribution
// or the GNU Library General Public License (LGPL) version 2 or later
// <http://www.gnu.org/copyleft/lgpl.html>
//
//

#ifndef _TidyParser_h_
#define _TidyParser_h_

#include "HtStdHeader.h"
#include "DocumentRef.h"
#include "CLuceneAPI.h"

//
// include the two HTMLtidy headers
// 
#include "tidy.h"
#include "buffio.h"

class TidyParser
{
    public:

    //
    // Construction/Destruction
    //
    TidyParser();
    ~TidyParser();

    //
    // recieve the pointer to the Clucene document, and get the TidyDoc
    // all set up and ready to parse a buffer of text. also clear the
    // URLlist and reset all the position flags. the encoding is sent in a char*
    //
    void initialize(DocumentRef *, char*);

    //
    // insert a field into the CLucene doc directly
    //
    void insertField(const char*, const char*);

    //
    // parse the buffer, return a set of
    // URLs seen during parsing
    // 
    std::set<std::string> parseDoc(char*);

    bool NoIndex() { return noIndex; }
 
    private:

    //
    // parsed HTML document
    // 
    TidyDoc tdoc;

    //
    // Will get the words from the parsed HTML document
    // and eventually will get inserted into CLucene
    //
    DocumentRef * CLuceneDoc;

    //
    // list of URLs seen during parsing. using
    // a std::set<> here so that the URLs are unique
    //
    set<string> URLlist;

    set<string> stemWords;

    //
    // position flags
    // 
    bool inHead;
    bool inTitle;
    bool inBody;
    bool inHeading;

    //
    // document/link handling tags
    //
    bool noIndex;
    bool noFollow;

    //
    // recursive call to traverse document parse tree
    //
    void nodeTraverse( TidyNode tnod );
    
    //
    // detect a node type and change states
    //
    void stateChanger(TidyNode tnod, bool newState);

    //
    // kill the TidyDoc
    //
    void release();

};

#endif

