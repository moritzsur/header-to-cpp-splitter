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
    mainScope = HeaderScope("", docString)

    print(mainScope.get_structure_str())
    quit()

    # hString = mainScope.get_h_string()
    return ["", ""] #todo


# uses composite pattern to 
class HeaderScope:

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

            childPos = self.__get_child_content_position(scopeContent)
            childStart = childPos[0]
            childEnd = childPos[1]

            childStr = scopeContent[childStart:childEnd + 1]
            childPrefixStr = self.__get_child_prefix(scopeContent, childStart)
            fullStr = childPrefixStr + childStr

            scopeWithChild = scopeContent
            scopeContent = scopeContent.replace(fullStr, "", 1) 
            child = HeaderScope(childPrefixStr, childStr)
            
            if not self.__validate_child(child, childEnd, scopeWithChild):
                continue
            
            self.childs.append(child)

    # validates that a leaf should be added to composite structure
    def __validate_child(self, childScope, childEndIndex: int, scopeStringWithChildStr: str) -> bool:
        if not childScope.is_leaf:
            return True
        
        content = childScope.fullContent
        
        # ignore scopes that are smaller than one line
        if content.count(";") < 2:
            return False

        #ignore scopes that are leafs and end with ";" - enums or variables
        if childEndIndex + 1 < len(scopeStringWithChildStr) and scopeStringWithChildStr[childEndIndex + 1] == ";":
            return False

        return True
        

    def __get_child_content_position(self, scopeContent : str):
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

    def __get_child_prefix(self, content : str, childStartIndex: int) -> str:
        tStr = content[0:childStartIndex]
        # todo: remove curlys in normal braces (fix constructor prefixes)
        # the indexes of content removed has to be remembered
        #indexesRemoved = self.__remove_brace_content(tStr)

        startIndex = max(max([tStr.find("}"), tStr.find(";")]), 0)
        # add to start index for every content removed before it 
        
        assert startIndex > -1
        assert startIndex < childStartIndex
        
        prefix = content[startIndex:childStartIndex]
        prefix = StringProcessing.remove_any_from_start(prefix, " ;")
        return prefix
