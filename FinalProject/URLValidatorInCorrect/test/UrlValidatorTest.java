

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Arrays;

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {

    String[] validSchemes = { "ftp://", "http://", "https://"};
    char[] alpha = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ".toCharArray();
    char[] alphaNum = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789".toCharArray();
    char[] allChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789_-*/$".toCharArray();
    // Here we need to read the file and import all valid TLD's
    String[] validTLD = {".com", ".org", ".gov"};

   public UrlValidatorTest(String testName) {
      super(testName);
   }


   public void testManualTest() throws IOException
   {
	//You can use this function to implement your manual testing
	   String inputStr;
       long options =
               UrlValidator.ALLOW_2_SLASHES
                   //+ UrlValidator.ALLOW_ALL_SCHEMES
                   + UrlValidator.NO_FRAGMENTS;
       UrlValidator urlVal = new UrlValidator(null, null, options);

	   do {
		   System.out.print("Enter the URL you would like to test: ");
		   BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
		   inputStr = in.readLine();

		   // Run input through URLValidator
		   if (inputStr.contentEquals("quit") == false) {
			   try {
				   boolean result = urlVal.isValid(inputStr);
				   // Print results from URLValidator
				   System.out.println("URLValidator returned " + result + " for input URL: " + inputStr);
			   } catch (Error e) {
				   System.out.println("Error caught: " + e);
			   }
		   }


	   } while (inputStr.contentEquals("quit") == false);


	   System.out.println("Quitting manual testing");
   }

   // method testIsValid is used for unit/programming based testing
   // each component has two hard-coded arrays,
   // the first of valid examples of the component, the second of invalid examples
   // it creates all combinations for these component arrays and validates the expected results
   public void testIsValid()
   {
	   //You can use this function for programming based testing
     int[] idxes = {0,1};
     // boolean true = true;
     // boolean false = 0;
     // Each component except queries has two arrays, the first of valid examples of the component, the second of invalid examples
     String[][] schemes = {validSchemes,
       {"htp:/"}};
     String[][] authorities = {
       {"1.1.1.1", "255.255.255.255","google.com","www.hello.org"},
       {"256.255.255.255", "aa", "1.2.3.4.5", "mine.beers"}};
     String[][] ports = {
       {":80", ":255", ":65535", ""},
       {":-1", ":65536", ":70000", ":a"}};
     String[][] paths = {
       {"/12894", "/check.txt", "/.../", "/.", "/$d6"},
       {"/../filepath","/#/filepath","/.."}};
     String[] queries = {"?a=b", ""};


     // Check each invalid component arrays combined only with all valid arrays
     // And then one test for combinations of all valid arrays
     // This would eliminate combinations like testURLs(schemes[1], authorities[1], ports[0], paths[0], queries, 0);
     // Where two of the arrays have all invalid values
     testURLs(schemes[0], authorities[0], ports[0], paths[0], queries, true);
     testURLs(schemes[1], authorities[0], ports[0], paths[0], queries, false);
     testURLs(schemes[0], authorities[1], ports[0], paths[0], queries, false);
     testURLs(schemes[0], authorities[0], ports[1], paths[0], queries, false);
     testURLs(schemes[0], authorities[0], ports[0], paths[1], queries, false);
   }

   // method testRandomURLs is used for random testing of URL's
   // each component has two randomly generated arrays,
   // the first of valid examples of the component, the second of invalid examples
   // it creates all combinations for these component arrays and validates the expected results
   public void testRandomURLs()
   {
     int[] idxes = {0,1};
     // Each component has two arrays, the first of valid examples of the component, the second of invalid examples
     // Most of these are generated randomly through a function call
     String[][] schemes = {validSchemes, generateInvalidScheme()};
     String[][] authorities = {generateValidAuthority(), generateInvalidAuthority()};
     String[][] ports = {generateValidPorts(), generateInvalidPorts()};
     String[][] paths = {generateValidPaths(), generateInvalidPaths()};
     String[] queries = {""};

     // Check each invalid component arrays combined only with all valid arrays
     // And then one test for combinations of all valid arrays
     // This would eliminate combinations like testURLs(schemes[1], authorities[1], ports[0], paths[0], queries, 0);
     // Where two of the arrays have all invalid values
     testURLs(schemes[0], authorities[0], ports[0], paths[0], queries, true);
     testURLs(schemes[1], authorities[0], ports[0], paths[0], queries, false);
     testURLs(schemes[0], authorities[1], ports[0], paths[0], queries, false);
     testURLs(schemes[0], authorities[0], ports[1], paths[0], queries, false);
     testURLs(schemes[0], authorities[0], ports[0], paths[1], queries, false);
   }

   // testURLs is given an array of examples for each component of a URL, and a boolean value of whether
   // all of the combinations of the given arrays should evaluate to true or false
   // calls UrlValidator.isValid and checks that the result is equal to the expected value
   public void testURLs(String[] schemes, String[]authorities, String[] ports, String[] paths, String[] queries, boolean v)
   {
     int errorCount = 0;
     long options =
             UrlValidator.ALLOW_2_SLASHES
                 // + UrlValidator.ALLOW_ALL_SCHEMES
                 + UrlValidator.NO_FRAGMENTS;
     UrlValidator urlVal = new UrlValidator(null, null, options);

     // Create all combinations of each of the input array components
     for(String s : schemes){
       for(String a : authorities){
         for(String p: ports){
           for(String p2 : paths){
             for(String q : queries){
      			   // Print results from URLValidator
               try {
                 boolean result = urlVal.isValid(s + a + p + p2 + q);
                 // System.out.println(result);
              	 if(v != result){
                   errorCount++;
                   System.out.println("FAILURE URLValidator returned " + result + " for input URL: " + s + a + p + p2 + q + " expected: " + v);
                 }
               } catch (Error e) {
              	 System.out.println("Error caught: " + e);
               }
             }
           }
         }
       }
     }
     System.out.println("Total Failures: " + errorCount);
   }

   // This method generates and returns an array of invalid URL schemes
   // The schemes are based on valid schemes, altering or deleting a character
   private String[] generateInvalidScheme(){
    String[] invalidSchemes = {"", "", "", ""};
    for (int i = 0; i < invalidSchemes.length; i++) {
      int randomChar = (int)(Math.random() * allChars.length);
      int randomPos = (int)(Math.random() * validSchemes[0].length());
      char[] tmp = validSchemes[0].toCharArray();
      if (tmp[randomPos] != allChars[randomChar]) {
        tmp[randomPos] = allChars[randomChar];
      } else {
        for(int x=randomPos;x<tmp.length-1;x++)
         {
             tmp[x]=tmp[x+1];
         }
      }
      invalidSchemes[i] = new String(tmp);

      // System.out.println(invalidSchemes[i]);
    }
    return invalidSchemes;
  }

  // This method generates a random valid authority by creating a random string of 1-100
  // alphanumeric character and then appending a random valid TLD
  private String[] generateValidAuthority(){
   String[] rtn = {"", "", "", ""};
   for (int i = 0; i < rtn.length; i++) {
     int randomLength = (int)(Math.random() * 40 + 1);
     for (int j=0; j<randomLength; j++){
       int randomChar = (int)(Math.random() * alphaNum.length);
       rtn[i] += alphaNum[randomChar];
     }
     int randomTLD = (int)(Math.random() * validTLD.length);
     rtn[i] += validTLD[randomTLD];
     // System.out.println(rtn[i]);
   }
   return rtn;
 }

 // This method generates a random valid authority by creating a random string of 0-100
 // alphanumeric character and then appending a random invalid TLD
 private String[] generateInvalidAuthority(){
  String[] rtn = {"", "", "", ""};
  // Main loop to create all of the authority strings
  for (int i = 0; i < rtn.length; i++) {
    // Create a random beginning domain
    int randomLength = (int)(Math.random() * 53);
    for (int j=0; j<randomLength; j++){
      int randomChar = (int)(Math.random() * allChars.length);
      rtn[i] += allChars[randomChar];
    }

    int pos = 0;
    randomLength = (int)(Math.random() * 10);
    char[] authority = new char[randomLength];
    // Loop until a random invalid TLD is generated
    while(pos >= 0){
      for (int j=0; j<randomLength; j++){
        int randomChar = (int)(Math.random() * allChars.length);
        authority[j] = allChars[randomChar];
      }
      pos = Arrays.binarySearch(validTLD, new String(authority));
    }
    // Append the TLD to the authority string
    rtn[i] = rtn[i] + "." + new String(authority);

    // System.out.println(rtn[i]);
  }
  return rtn;
}

// This method generates a valid port to append to the URL
// Valid ports range from 0-65535 the last value is just an empty string
private String[] generateValidPorts(){
 String[] rtn = {":", ":",""};
 for (int i = 0; i < rtn.length-1; i++) {
   int random = (int)(Math.random() * 65535 + 1);
   rtn[i] = rtn[i] + random;
   // System.out.println(rtn[i]);
 }
 return rtn;
}

// This method generates invalid ports to append to the URL
// Valid ports range from 0-65535
private String[] generateInvalidPorts(){
 String[] rtn = {":", ":", ":", ":", ":"};
 // Add random ports greater than the max 65535
 for (int i = 0; i < rtn.length - 3; i++) {
   int random = (int)(Math.random() * 100 + 65536);
   rtn[i] = rtn[i] + random;
   // System.out.println(rtn[i]);
 }
 // Add two random negative ports
 rtn[rtn.length - 1] = rtn[rtn.length - 1] + -(int)(Math.random() * 100 + 1);
 rtn[rtn.length - 2] = rtn[rtn.length - 2] + -(int)(Math.random() * 100 + 1);
 // Add a random character
 int randomChar = (int)(Math.random() * alpha.length);
 rtn[rtn.length - 3] = rtn[rtn.length - 3] + alpha[randomChar];

 return rtn;
}

// This method generates a valid path to append to the URL
// Valid paths can contain any letter, number, special character combination
private String[] generateValidPaths(){
 String[] rtn = {"/", "/", "/", "/"};
 for (int i = 0; i < rtn.length; i++) {
   // Create a random path length
   int randomLength = (int)(Math.random() * 100);
   for (int j=0; j<randomLength; j++){
     int randomChar = (int)(Math.random() * allChars.length);
     rtn[i] += allChars[randomChar];
   }
   // System.out.println(rtn[i]);
 }
 return rtn;
}

// This method generates invalid paths to append to the URL
// Invalid paths contain ".."
private String[] generateInvalidPaths(){
 String[] rtn = {};
 for (int i = 0; i < rtn.length; i++) {
   // Create a random path length
   int randomLength = (int)(Math.random() * 50);
   char[] tmpA = new char[randomLength];
   for (int j=0; j<randomLength; j++){
     int randomChar = (int)(Math.random() * allChars.length);
     tmpA[j] += allChars[randomChar];
   }
   rtn[i] += new String(tmpA);

   // Add invalid ".."
   rtn[i] += "/../";
   // Create a random path length
   randomLength = (int)(Math.random() * 50);
   char[] tmpB = new char[randomLength];
   for (int j=0; j<randomLength; j++){
     int randomChar = (int)(Math.random() * allChars.length);
     tmpB[j] += allChars[randomChar];
   }
   rtn[i] += new String(tmpB);
   // System.out.println(rtn[i]);
 }
 return rtn;
}



}
