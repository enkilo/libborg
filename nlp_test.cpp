//#define BOOST_SPIRIT_DUMP_PARSETREE_AS_XML
//#define BOOST_SPIRIT_DEBUG
#include <string>
#include <map>
#include <iostream>
#include <boost/bind.hpp>
#include <boost/spirit/core.hpp>
#include <boost/spirit/tree/parse_tree.hpp>
#include <boost/spirit/utility/lists.hpp>

#ifdef BOOST_SPIRIT_DUMP_PARSETREE_AS_XML
#include <boost/spirit/tree/tree_to_xml.hpp>
#include <map>
#endif

#include <borg/nlp/grammar.hpp>
#include <borg/nlp/skipper.hpp>

using namespace boost;
using namespace spirit;
using namespace borg;
using namespace nlp;
using namespace std;

typedef const char *iterator_t;
typedef tree_match<iterator_t> parse_tree_match_t;
typedef parse_tree_match_t::const_tree_iterator iter_t;

static map<parser_id, string> rule_names;
  
void pt_print(const iter_t &it, int depth = 0)
{
  cout << depth << "> name:'" << rule_names[it->value.id()] <<
    "', value:'" << string(it->value.begin(), it->value.end()) << "'" << endl;
  
  iter_t chi = it->children.begin();
  
  if(!it->children.size())
    return;
  
  while(chi != it->children.end())
  {
    pt_print(chi, depth + 1);
    ++chi;
  }
  
//  for_each(it->children.begin(), it->children.end(), bind(pt_print, _1, depth + 1));
}

void nlp_test()
{
  typedef pt_match_policy<iterator_t> match_policy_t;
  typedef scanner_policies<iteration_policy, match_policy_t, action_policy> scanner_policy_t;
  typedef scanner<iterator_t, scanner_policy_t> scanner_t;
  typedef rule<scanner_t> rule_t;
  
  string str1 = "These are words";
  string str2 = "This is a sentence.This is the second sentence.";

  //  grammar rules
  rule_t word, space, punct, sentence, text;
  rule_t integer, factor, term, expression;

  word = token_node_d[ +alpha_p/* >> (eol_p | space_p | blank_p)*/ ];

  space = +(space_p | blank_p | eol_p);
  
  punct = +punct_p;
//  sentence = list_p(word, space, punct);
  sentence = word >> *(space >> word) >> punct;
//  text = sentence >> *(space >> sentence);
  text = sentence >> *(text | sentence); //*(space >> sentence);
  
  skipper skip_p;
  nlp::grammar< nlp::traits<nlp::english> > g;
  
  const char *first = str2.c_str();
  tree_parse_info<> info = pt_parse(first, g);
  
  rule_names = g.rule_names;
/*  rule_names[g.word.id()] = "word";
  rule_names[g.space.id()] = "space";
  rule_names[g.punct.id()] = "punct";
  rule_names[g.sentence.id()] = "sentence";
  rule_names[g.text.id()] = "text";*/
  
  iter_t it = info.trees.begin();
  
  while(it != info.trees.end())
    pt_print(it), ++it;

//  iter_t children = it->children.begin();
  
  if(info.full)
  {
#if defined(BOOST_SPIRIT_DUMP_PARSETREE_AS_XML)
    // dump parse tree as XML
    tree_to_xml(cout, info.trees, expression, rule_names);
#endif
    // print the result
    std::cout << "parsing succeeded\n";
  }

//  skipper skip_p;
//  grammar< traits<english> > p;
  
//  parse_info<vector<char>::const_iterator> info =
//    parse(
}

int main()
{
  try
  {
    nlp_test();
  }
  catch(const exception &e)
  {
    cerr << "exception: " << e.what() << endl;
  }
  
}
