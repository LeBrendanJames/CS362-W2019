

import junit.framework.TestCase;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest() throws IOException
   {
	//You can use this function to implement your manual testing
	   String inputStr;
       long options =
               UrlValidator.ALLOW_2_SLASHES
                   + UrlValidator.ALLOW_ALL_SCHEMES
                   + UrlValidator.NO_FRAGMENTS;
       UrlValidator urlVal = new UrlValidator(null, null, options);
       
	   do {
		   System.out.print("Enter the URL you would like to test: ");
		   BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		   inputStr = in.readLine();
		   
		   // Run input through URLValidator
		   if (inputStr.contentEquals("quit") == false) {
			   boolean result = urlVal.isValid(inputStr);
			   // Print results from URLValidator
			   System.out.println("URLValidator returned " + result + " for input URL: " + inputStr);
		   }
		   
		   
	   } while (inputStr.contentEquals("quit") == false);
	   
	   
	   System.out.print("Quitting manual testing");
   }
   
   
   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   

   }
   
   public void testYourSecondPartition(){
		 //You can use this function to implement your Second Partition testing	   

   }
   //You need to create more test cases for your Partitions if you need to 
   
   public void testIsValid()
   {
	   //You can use this function for programming based testing

   }
   


}
