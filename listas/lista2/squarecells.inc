% squarecells.tex - create a table with square cells
% Will Robertson
% http://www.tug.org/pracjourn/2005-2/robertson/robertson.pdf
\usepackage{calc}
\newlength\celldim \newlength\fontheight \newlength\extraheight
\newcounter{sqcolumns}
\newcolumntype{S}{ @{}
  >{\centering \rule[-0.5\extraheight]{0pt}{\fontheight + \extraheight}}
  p{\celldim} @{} }
\newcolumntype{Z}{ @{} >{\centering} p{\celldim} @{} }
\newenvironment{squarecells}[1]
  {\setlength\celldim{2em}%
   \settoheight\fontheight{A}%
   \setlength\extraheight{\celldim - \fontheight}%
   \setcounter{sqcolumns}{#1 - 1}%
   \begin{tabular}{|S|*{\value{sqcolumns}}{Z|}}\hline}
% squarecells tabular goes here
  {\end{tabular}}
\newcommand\nl{\tabularnewline\hline}
