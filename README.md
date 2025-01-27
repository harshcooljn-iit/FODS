# FODS
This code finds all candidate keys of a relation R given all its attributes as inputs and its set of functional dependencies.<br/>
<br/>
Inputs:<br/>
1. Number of Attributes<br/>
2. All attributes<br/>
3. Number of FDs (FD = Functional Dependency)<br/>
4. All FDs<br/>
<br/>
Input Format: <br/>
&ensp;  Number of Attributes<br/>
&ensp; Space Seperated Attributes<br/>
&ensp;  Number of Functional dependencies<br/>
&ensp;  Description of each functional dependency on a new line<br/>
&ensp;  L R LHS RHS <br/><br/><br/><br/>
where L = # of attributes on LHS, R = # of attributes on RHS, LHS = space seperated attributes from LHS of FD, RHS = space seperated attributes from RHS of FD.
<br/>
Output: <br/>
Candidate keys (of minimal size)<br/>
<br/>
Example Input :<br/>
<img width="504" alt="FODS_Input_Example" src="https://github.com/user-attachments/assets/c8755ac9-6508-48b8-b549-968455976db2" />
<br/><br/>
Example Output:<br/>
 <img width="504" alt="FODS_Output_Example" src="https://github.com/user-attachments/assets/b7dc7468-b4d3-4292-875a-927afac1d8b1" />
<br/>
