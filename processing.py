
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

    # optimize file for analysis: replace tabs and newlines with space, remove multiple spaces in a row
    docString = replace_special_chars(docString)
    docString = remove_multi_spaces(docString)

    #docString = process_formatted(docString)
    scopes = scopes_from_string(docString)
    
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

class Scope:
    def __init__(self, content, name = ""):
        self.content = content
        self.__set_name()
        self.__build_childs()

    def __set_name():
        pass #TODO

    def __build_childs(self):
        self.childs = []
        if self.content == "":
            return

        while True:
            section = StrSection(self.content, "{", "}")
            if not section.exists():
                return
            
            self.childs.append(Scope(section.content))
            self.content = section.input_without_section()

        

def scopes_from_string(string):

    charIndex = 0
    while charIndex < len(string):
        char = string(charIndex)
        
        

        charIndex += 1

def get_scope_name(string):
    tempWords = string.rsplit(" ", 2)
    if len(tempWords) > 1:
        secLW = tempWords[1]
        if secLW == "struct" or secLW == "namespace" or secLW == "class":
            return tempWords[0]
    
    return ""
