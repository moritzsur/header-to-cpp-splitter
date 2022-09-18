
# this is all about processing, no file stuff



from email.header import Header


def remove_sections(string, startChars, endChars, endCharsToLeave = 0):

    while string.find(startChars) > -1:
        startIndex = string.find(startChars)
        endIndex = string[startIndex + 1:].find(endChars) 
        if endIndex < 0:
            return string
        
        endIndex += startIndex + 1
        startStr = string[0:startIndex]
        endStr = string[endIndex + len(endChars) - endCharsToLeave:len(string)]
        string = startStr + endStr

    return string

def remove_section_content(string, startChars, endChars):
    lastIndex = 0
    outString = ""
    while True:
        strToSearch = string[lastIndex + 1:]
        startIndex = strToSearch.find(startChars)
        endIndex = strToSearch[startIndex + 1:].find(endChars) 

        if startIndex < 0 or endIndex < 0:
            break

        outString += strToSearch[:startIndex + 1] + strToSearch[endIndex + startIndex + 1:]
        lastIndex += endIndex
    
    return outString

def remove_comments(string):
    string = remove_sections(string, "//", "\n", 1)
    string = remove_sections(string, "/*", "*/\n")
    string = remove_sections(string, "/*", "*/")
    return string

def remove_preprocessor_defs(string):
    string = remove_sections(string, "#", "\n")
    return string

def remove_string_content(string):
    string = remove_section_content(string, "\"", "\"")
    return string

def replace_special_chars(string):
    escChars = "\a\b\f\n\r\t\v"
    for char in escChars:
        string = string.replace(char, " ")

    return string

def remove_multi_spaces(string):
    while string.find("  ") > -1:
        string = string.replace("  ", " ")
    return string

# the core function for processing a headers text
def process_raw_lines(hLines, cppLines):
    docString = ""
    for line in hLines:
        docString = docString + line

    docString = remove_comments(docString)
    docString = remove_preprocessor_defs(docString)
    # needs fix
    # docString = remove_string_content(docString)

    # optimizing file for analysis: replace tabs and newlines with space, remove multiple spaces in a row
    docString = replace_special_chars(docString)
    docString = remove_multi_spaces(docString)

    mainScope = HeaderScope("", docString, list())
    hString = mainScope.get_h_string()
    cppString = mainScope.get_cpp_string()
    
    return ["", docString]

class StrSection:
    def __init__(self, inputString, startChars, endChars):
        self.__startChars = startChars
        self.__endChars = endChars
        self.__content = ""
        self.__startIndex = inputString.find(startChars) 
        tString = inputString[self.__startIndex:]
        self.__endIndex = tString.find(endChars)
        if self.__endIndex > -1:
            self.__endIndex += self.__startIndex

        if not self.exists():
            return

        self.content = inputString[self.__startIndex:self.__endIndex + 1]

    def get_position(self):
        return self.__startIndex, self.__endIndex

    def exists(self):
        return self.__startIndex + self.__endIndex > -1

    def remove_from_str(self, string):
        other = StrSection(string, self.__startChars, self.__endChars)
        if not other.exists():
            return string

        string = string[0:other.__startIndex] + string[other.__endIndex + 1:]

        return string

    def input_without_section(self):
        return self.remove_from_str(self.content)

    def get_content(self):
        return self.__content

# uses composite pattern to 
class HeaderScope:

    #prefix is the text before the scope starts. Could contain struct, enum, method declaration etc.
    def __init__(self, prefix, content, surroundingScopes):
        self.TYPE_STR_METHOD = "METHOD"
        self.TYPE_STR_SKT_CLS_NAM = "STRUCT_CLASS_NAMESPACE"

        assert isinstance(surroundingScopes, list)
        self.__set_content(content)
        self.__set_properties(surroundingScopes, prefix)

        self.childs = []
        if self.type == self.TYPE_STR_SKT_CLS_NAM:
            self.__build_childs()

    def __set_content(self, content):
        if(content[0] == "{"):
            content = content[1:]
            lastChar = content[:len(content) - 1]
            assert lastChar == "}"
            content = content[0:lastChar]
        self.content = content

    def __set_properties(self, surScopes, prefix):
        self.type = self.scope_name_from_prefix(prefix)
        self.scopes = surScopes + self.scope_name_from_prefix(prefix)

    def __build_childs(self):
        if self.content == "":
            return

        while True:
            childContent = StrSection(self.content, "{", "}")
            if not childContent.exists():
                return
            
            prefix = self.__get_child_prefix(childContent.get_position()[0])

            self.childs.append(HeaderScope(childContent.get_content()))
            self.content = childContent.input_without_section()

    def scope_name_from_prefix(self, prefix):
        type = HeaderScope.scope_type_from_prefix(prefix)
        if type == self.TYPE_STR_METHOD:
            return ""

    def scope_type_from_prefix(self, prefix):
        #if the prefix content is a method declaration, return "_method", else return the name
        return self.TYPE_STR_METHOD
        pass

    def __get_child_prefix(self, childStartIndex):
        tStr = self.content[0:childStartIndex]
        sIndex = max([tStr.find("}"), tStr.find(";")])
        assert sIndex > -1
        assert sIndex < childStartIndex
        prefix = self.content[sIndex:childStartIndex]
        print(prefix)
        return prefix

    def get_cpp_string(self):
        cppString = ""
        for child in self.childs:
            cppString += child.get_cpp_string()

        

    def get_h_string():
        pass

#def get_scope_name(string):
#    tempWords = string.rsplit(" ", 2)
#    if len(tempWords) > 1:
#        secLW = tempWords[1]
#        if secLW == "struct" or secLW == "namespace" or secLW == "class":
#            return tempWords[0]
#    
#    return ""
