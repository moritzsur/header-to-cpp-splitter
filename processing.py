from typing import List
import StringProcessing

# this is all about processing, no file stuff

# the core function for processing a headers text
def process_raw_lines(hLines, cppLines):
    docString = ""
    for line in hLines:
        docString = docString + line

    numCurlyOpen = docString.count("{")
    numCurlyClose = docString.count("}")
    assert numCurlyOpen == numCurlyOpen

    docString = StringProcessing.remove_comments(docString)
    docString = StringProcessing.remove_preprocessor_defs(docString)
    
    # needs fix
    # docString = remove_string_content(docString)

    # optimizing file for analysis: replace tabs and newlines with space, remove multiple spaces in a row
    docString = StringProcessing.replace_special_chars(docString)
    docString = StringProcessing.remove_multi_spaces(docString)

    assert docString.count("{") == numCurlyOpen
    assert docString.count("}") == numCurlyClose
    mainScope = Scope("", docString)

    print(mainScope.get_structure_str())
    quit()

    # hString = mainScope.get_h_string()
    return ["", ""] #todo


# uses composite pattern to represent the scopes in a header file
class Scope:

    #prefix is the text before the scope starts. Could contain struct, enum, method declaration etc.
    def __init__(self, prefix: str, content: str):
        content      = StringProcessing.remove_surrounding_curlys(content)
        self.is_leaf = StringProcessing.is_leaf_scope_from_prefix(prefix) #is true when this scope should have no child scopes
        self.name    = self.__name_from_prefix(prefix) #the names that will be added to create the method in the cpp file - name1::name2::name3 { doStuff; }
        self.fullPrefix = prefix
        self.fullContent = content        
        self.__build_childs(content)

    def get_h_string(self) -> str:
        return ""

    def get_cpp_string(self):
        cppString = ""

        for child in self.childs:
            cppString += child.get_cpp_string()

    def get_structure_str(self) -> str:
        output = "\n" 
        if(self.is_leaf):
            output += "LEAF "
        output += self.name
        for child in self.childs:
            chStr = child.get_structure_str()
            chLines = chStr.splitlines(True)
            chStr = ""

            for line in chLines:
                line = "   " + line
                chStr += line

            output += chStr
        
        return output

    def __name_from_prefix(self, scopePrefix: str) -> str:
        if StringProcessing.is_leaf_scope_from_prefix(scopePrefix):
            scopePrefix = StringProcessing.remove_access_specifiers(scopePrefix)
            scopePrefix = StringProcessing.remove_any_from_start(scopePrefix, " ")
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
        name = StringProcessing.to_alpha(name)
        return name

    def __build_childs(self, scopeContent: str):
        self.childs = []
        if scopeContent == "" or self.is_leaf: # ignore method content
            return

        unprocessedContent = scopeContent
        while True:
            childStartIndex = unprocessedContent.find("{")
            if childStartIndex < 0: 
                return

            childBuilder = ScopeChildBuilder(unprocessedContent)
            unprocessedContent = unprocessedContent.replace(childBuilder.full_str, "", 1) # remove before validation to avoid finding that scope again
            
            if not childBuilder.created_valid():
                continue
            
            self.childs.append(childBuilder.scope)

#creates first Scope from the input string
class ScopeChildBuilder:
    def __init__(self, input : str):
        self.__input = input

        childPos = self.__get_content_position(input)
        self.startPos = childPos[0]
        self.endPos = childPos[1]
        self.content = input[self.startPos:self.endPos + 1]
        self.prefix = self.__get_prefix()

        self.scope = Scope (self.prefix, self.content)
        self.full_str = self.prefix + self.content
        
    # validates that a leaf should be added to composite structure 
    def created_valid(self) -> bool:
        if not self.scope.is_leaf:
            return True
        
        content = self.scope.fullContent
        
        # ignore scopes that are smaller than one line
        if content.count(";") < 2:
            return False

        #ignore scopes that are leafs and end with ";" - enums or variables
        if self.endPos + 1 < len(self.__input) and self.__input[self.endPos + 1] == ";":
            return False

        # todo add test for templates, since template are no scopes that should be cared about
        if self.prefix.find("template") > -1:
            return False

        return True

    #identifies scopes in a given string and returns it start and end pos
    def __get_content_position(self, parentContent : str):
        curlyBraceCounter = 0
        endIndex = -1
        startIndex = parentContent.find("{")
        content = parentContent[startIndex:]

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

    # looks for the scope prefix with the scope position as a starting point
    def __get_prefix(self) -> str:
        tStr = self.__input[0:self.startPos]

        # indexesRemoved = StringProcessing.remove_brace_content(tStr) #test this (fixes constructors)

        startIndex = max(max(tStr.find("}"), tStr.find(";")), 0)
        # add to start index for every content removed before it 
        
        assert startIndex > -1
        assert startIndex < self.startPos
        
        prefix = self.__input[startIndex:self.startPos]
        prefix = StringProcessing.remove_any_from_start(prefix, " ;")
        return prefix
