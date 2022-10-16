
# this is all about processing, no file stuff

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
    string = remove_sections(string, "/*", "*/")
    string = remove_sections(string, "/*", "*/")
    return string

def remove_preprocessor_defs(string : str) -> str:
    lines = string.splitlines(True)
    string = ""

    for i, line in enumerate(lines):
        if line.startswith("#"):
            lines.pop(i)

    for line in lines:
        string += line

    # string = remove_sections(string, "#", "\n")
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

    numCurlyOpen = docString.count("{")
    numCurlyClose = docString.count("}")
    assert numCurlyOpen == numCurlyOpen

    docString = remove_comments(docString)
    numCurlyOpen = docString.count("{")
    numCurlyClose = docString.count("}")
    docString = remove_preprocessor_defs(docString)
    numCurlyOpen = docString.count("{")
    numCurlyClose = docString.count("}")
    
    # needs fix
    # docString = remove_string_content(docString)

    # optimizing file for analysis: replace tabs and newlines with space, remove multiple spaces in a row
    docString = replace_special_chars(docString)
    numCurlyOpen = docString.count("{")
    numCurlyClose = docString.count("}")
    docString = remove_multi_spaces(docString)
    numCurlyOpen = docString.count("{")
    numCurlyClose = docString.count("}")

    assert docString.count("{") == numCurlyOpen
    assert docString.count("}") == numCurlyClose
    mainScope = HeaderScope("", docString)

    print(mainScope.get_structure_str())
    quit()

    # hString = mainScope.get_h_string()
    return ["", ""] #todo

class StrSection:
    #looks for first occurence of startChars and first occurence of endChars in [startCharIndex:]
    def __init__(self, inputString, startChars, endChars):
        self.startChars = startChars
        self.endChars = endChars
        self.__content = ""
        self.startIndex = inputString.find(startChars) 
        self.endIndex = -1
        
        if self.startIndex > -1:
            tString = inputString[self.startIndex:]
            self.endIndex = tString.find(endChars)
            if self.endIndex > -1:
                self.endIndex += self.startIndex

        if not self.exists():
            self.content = ""
            return

        self.content = inputString[self.startIndex:self.endIndex + 1]

    def exists(self):
        return self.startIndex > -1 and self.endIndex > -1

    def remove_from_str(self, string):
        other = StrSection(string, self.startChars, self.endChars)
        if not other.exists():
            return string

        string = string[0:other.startIndex] + string[other.endIndex + 1:]

        return string

    def input_without_section(self):
        return self.remove_from_str(self.content)

    def get_content(self):
        return self.__content

# uses composite pattern to 
class HeaderScope:

    #prefix is the text before the scope starts. Could contain struct, enum, method declaration etc.
    def __init__(self, prefix: str, content: str):
        content      = self.remove_surrounding_curlys(content)
        self.is_leaf = self.__is_leaf_from_prefix(prefix) #is true when this scope should have no child scopes
        self.name    = self.__name_from_prefix(prefix) #the names that will be added to create the method in the cpp file - name1::name2::name3 { doStuff; }
        # print(f"scopename: {self.name}")
        
        self.__build_childs(content)

    def remove_surrounding_curlys(self, strToUpdate: str) -> str:
        if(len(strToUpdate) < 1):
            return ""
        if(strToUpdate[0] == "{"):
            assert strToUpdate[-1] == "}"
            return strToUpdate[1:-1]

        return strToUpdate

    def get_structure_str(self) -> str:
        output = "\n" + self.name
        for child in self.childs:
            chStr = child.get_structure_str()
            chLines = chStr.splitlines(True)
            chStr = ""

            for line in chLines:
                line = "   " + line
                chStr += line

            output += chStr
        
        return output

    def __is_leaf_from_prefix(self, prefix: str) -> bool:
        if(prefix == ""):
            return False
        if(prefix.find("class ") > -1):
            return False
        if(prefix.find("struct ") > -1):
            return False
        if(prefix.find("namespace ") > -1):
            return False
        return True

    def __name_from_prefix(self, scopePrefix: str) -> str:
        if self.__is_leaf_from_prefix(scopePrefix):
            return scopePrefix
        
        #if this is a class struct or namespace, this should return the corresponding name
        sIndex = scopePrefix.find("class ")
        if sIndex < 0:
            sIndex = scopePrefix.find("struct ")
        if sIndex < 0:
            sIndex = scopePrefix.find("namespace ")

        words = scopePrefix[sIndex:].split(" ")
        if len(words) < 2:
            return ""
        name = words[1]
        name = name.replace("{", "")
        return name

    def __build_childs(self, scopeContent: str):
        self.childs = []
        if scopeContent == "" or self.is_leaf: # ignore method content
            return

        while True:
            childStartIndex = scopeContent.find("{")
            if childStartIndex < 0: 
                return

            childPos = self.get_child_content_position(scopeContent)
            childStart = childPos[0]
            childEnd = childPos[1]

            childStr = scopeContent[childStart:childEnd + 1]
            childPrefixStr = self.get_child_prefix(scopeContent, childStart)
            fullStr = childPrefixStr + childStr

            self.childs.append(HeaderScope(childPrefixStr, childStr))
            scopeContent = scopeContent.replace(fullStr, "", 1) 
            
    def get_child_content_position(self, scopeContent : str):
        curlyBraceCounter = 0
        endIndex = -1
        startIndex = scopeContent.find("{")
        content = scopeContent[startIndex:]

        numOpen = content.count("{")  
        numClose = content.count("}")
        assert numOpen == numClose

        for i, char in enumerate(content):
            if char == "{":
                curlyBraceCounter += 1
            if char == "}":
                curlyBraceCounter += -1
            if curlyBraceCounter == 0:
                endIndex = i
                return startIndex, startIndex + endIndex
        
        assert False
        return 0, 0

    def get_child_prefix(self, content : str, childStartIndex: int) -> str:
        tStr = content[0:childStartIndex]
        sIndex = max([tStr.find("}"), tStr.find(";")]) + 1
        assert sIndex > -1
        assert sIndex < childStartIndex
        prefix = content[sIndex:childStartIndex]
        # print(prefix)
        return prefix

    def get_cpp_string(self):
        cppString = ""
        for child in self.childs:
            cppString += child.get_cpp_string()

        

    def get_h_string() -> str:
        return ""

#def get_scope_name(string):
#    tempWords = string.rsplit(" ", 2)
#    if len(tempWords) > 1:
#        secLW = tempWords[1]
#        if secLW == "struct" or secLW == "namespace" or secLW == "class":
#            return tempWords[0]
#    
#    return ""
