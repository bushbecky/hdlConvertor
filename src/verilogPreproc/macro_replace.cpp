#include "../verilogPreproc/macro_replace.h"


macro_replace::macro_replace(std::string macro_name, std::string replace, std::vector<std::string> arg){
	data.tmplate_name = macro_name;
	data.tmplate = replace;
	data.args = arg;
}

macro_replace::~macro_replace() {
}

// return false to skip this find because it is 
// from an already substitution of the same macro replacement
bool macro_replace::check_interval(size_t start) {
  for (auto paire:_substituate) {
    //printf("{%li,%li}\n",paire.first,paire.second);
    if ( (paire.first <= start) && (start < paire.first+paire.second)){
      return true;
    }
  }
  return false;
}
/*
 * Look for String literal. In order to forbid them to be change by replacement
 */
void macro_replace::look4stringLiteral(std::string tmpl) {
  size_t start_pos = 0;
  size_t pos1 = -1;
  while((start_pos = tmpl.find('"', start_pos)) != std::string::npos) {
    if (pos1 == -1 && (start_pos != 0 && tmpl[start_pos-1]!='`' || start_pos == 0) ) {
      pos1 = start_pos;
    }
    else if (pos1 != -1 && tmpl[start_pos-1]!= '`') {
      size_t length = start_pos - pos1;
      _substituate.push_back(std::make_pair(pos1,length));
      pos1 = -1;
    }
    start_pos += 1;
  }
}

void macro_replace::replaceAll(std::string& str, const std::string& from, const std::string& to) {
  if(from.empty())
    return;
  size_t start_pos = 0;
  while((start_pos = str.find(from, start_pos)) != std::string::npos) {
     /*	
        printf("-->%s\n",str.c_str());
        printf("-->%li %li\n",start_pos,from.length());
        printf("-->%s\n",to.c_str());
	printf("-->%c\n",str[start_pos+from.length()]);
*/
    if( not (
          (('a' <= str[start_pos+from.length()]) && (str[start_pos+from.length()] <='z')) ||
          (('A' <= str[start_pos+from.length()]) && (str[start_pos+from.length()] <='Z')) ||
          (('0' <= str[start_pos+from.length()]) && (str[start_pos+from.length()] <='9')) ||
          ('_' == str[start_pos+from.length()]) || ('$' == str[start_pos+from.length()]) ||
	  ('(' == str[start_pos+from.length()]) || ('[' == str[start_pos+from.length()]) ||
	  ('{' == str[start_pos+from.length()]) ||
	  
	  check_interval(start_pos) //check the find is in the result of a substitution of the same macro_replacement

          )
      ) {
	    //printf("replacement\n");
      /*
       * Test what is next character. If next character is part of [a-zA-Z0-9_$([{] then it is not what we have to replace.
       * 19.3.1 `define
       * The text specified for macro text shall not be split across the following lexical tokens:
       *   Comments
       *   Numbers
       *   Strings
       *   Identifiers
       *   Keywords
       *   Operators
       * */
      str.replace(start_pos, from.length(), to);
      unsigned long int i = 0;
      for (auto a: _substituate) {
	 //printf("%li < %li\n",start_pos,a.first );
         if (start_pos < a.first) {
		 //a->first += to.length();
		 _substituate.at(i) = std::make_pair(a.first+to.length(),a.second);
	 }
	 i++;
      }
      //for (auto paire:_substituate) {
      //  printf("[%li,%li]\n",paire.first,paire.second);
      //}
      _substituate.push_back(std::make_pair(start_pos,to.length()));
    }
    start_pos += 1;
  }
}

std::string macro_replace::replace(std::vector<std::string> arg) {

    std::string returnString;

    if (!data.tmplate.empty()) {
      returnString = data.tmplate;

      if (arg.size() != data.args.size()) {
        std::string message =  "Missmatch in number of argument macro declaration "
	  + data.tmplate_name + " (" + 
          std::to_string(data.args.size()) + 
          ") and macro usage ("+std::to_string(arg.size())+')';
        throw parseException(message);
      }
      _substituate.clear();
      std::vector<std::string>::iterator macro= data.args.begin();
      std::vector<std::string>::iterator instance = arg.begin();
      for ( ; macro != data.args.end(); macro++, instance++) {
        replaceAll(returnString,*macro,*instance);
      }
    }
    else {
      //Macro can be empty
      //Example `define MODE1
      returnString = "";
    }
    return returnString;

}

std::string macro_replace::replace() {
  std::vector<std::string> null_vector;
  return replace(null_vector);
}



