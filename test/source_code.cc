#include "../include/source_code.h"

#include <gtest/gtest.h>

using namespace valgo;

TEST (SourceCode, set) {
	SourceCode code;
	EXPECT_EQ(code.draw_as_latex(), "\\begin{lstlisting}[language=,numbers=left,aboveskip=-2pt,belowskip=0pt,xleftmargin=12pt,basicstyle=\\small\\ttfamily,showstringspaces=false,numbersep=5pt,numberstyle=\\small\\ttfamily,columns=spaceflexible,keepspaces=true,tabsize=4,breaklines=true,commentstyle=\\color{gray},keywordstyle=\\color{blue}\\bfseries,stringstyle=\\color{purple}]\n"
"\\end{lstlisting}");
	code.set_lang("C++");
	EXPECT_EQ(code.draw_as_latex(), "\\begin{lstlisting}[language=C++,numbers=left,aboveskip=-2pt,belowskip=0pt,xleftmargin=12pt,basicstyle=\\small\\ttfamily,showstringspaces=false,numbersep=5pt,numberstyle=\\small\\ttfamily,columns=spaceflexible,keepspaces=true,tabsize=4,breaklines=true,commentstyle=\\color{gray},keywordstyle=\\color{blue}\\bfseries,stringstyle=\\color{purple}]\n"
							   "\\end{lstlisting}");
	code.set_code(
		"long long sp(long long p, long long w) { \n"
		"    if (w == 0) return 1;\n"
		"    if (w % 2) return sp(p, w - 1) * p;\n"
		"    long long f = sp(p, w / 2);\n"
		"    return f * f;\n"
		"}");

	EXPECT_EQ(code.draw_as_latex(), "\\begin{lstlisting}[language=C++,numbers=left,aboveskip=-2pt,belowskip=0pt,xleftmargin=12pt,basicstyle=\\small\\ttfamily,showstringspaces=false,numbersep=5pt,numberstyle=\\small\\ttfamily,columns=spaceflexible,keepspaces=true,tabsize=4,breaklines=true,commentstyle=\\color{gray},keywordstyle=\\color{blue}\\bfseries,stringstyle=\\color{purple}]\n"
"long long sp(long long p, long long w) { \n"
"    if (w == 0) return 1;\n"
"    if (w % 2) return sp(p, w - 1) * p;\n"
"    long long f = sp(p, w / 2);\n"
"    return f * f;\n"
"}\\end{lstlisting}");

	code.set_title("Szybkie potegowanie");

	EXPECT_EQ(code.draw_as_latex(), "\\begin{lstlisting}[language=C++,title=Szybkie potegowanie,numbers=left,aboveskip=-2pt,belowskip=0pt,xleftmargin=12pt,basicstyle=\\small\\ttfamily,showstringspaces=false,numbersep=5pt,numberstyle=\\small\\ttfamily,columns=spaceflexible,keepspaces=true,tabsize=4,breaklines=true,commentstyle=\\color{gray},keywordstyle=\\color{blue}\\bfseries,stringstyle=\\color{purple}]\n"
"long long sp(long long p, long long w) { \n"
"    if (w == 0) return 1;\n"
"    if (w % 2) return sp(p, w - 1) * p;\n"
"    long long f = sp(p, w / 2);\n"
"    return f * f;\n"
"}\\end{lstlisting}");
}

