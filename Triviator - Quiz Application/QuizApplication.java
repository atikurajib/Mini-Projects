import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

class Question {
    private String questionText;
    private String optionA;
    private String optionB;
    private String optionC;
    private String optionD;
    private String correctAnswer;

    public Question(String questionText, String optionA, String optionB, String optionC, String optionD, String correctAnswer) {
        this.questionText = questionText;
        this.optionA = optionA;
        this.optionB = optionB;
        this.optionC = optionC;
        this.optionD = optionD;
        this.correctAnswer = correctAnswer;
    }

    public String getQuestionText() {
        return questionText;
    }

    public String getOptionA() {
        return optionA;
    }

    public String getOptionB() {
        return optionB;
    }

    public String getOptionC() {
        return optionC;
    }

    public String getOptionD() {
        return optionD;
    }

    public String getCorrectAnswer() {
        return correctAnswer;
    }

    public boolean isCorrectAnswer(String answer) {
        return correctAnswer.equalsIgnoreCase(answer);
    }
}

public class QuizApplication {
    private static final String QUESTIONS_FILE = "questions.txt";
    private static final int SCORE_PER_QUESTION = 10;

    private List<Question> questions;
    private int score;
    private Scanner scanner;

    public QuizApplication() {
        this.scanner = new Scanner(System.in);
        this.questions = new ArrayList<>();
    }

    public void loadQuestions() throws FileNotFoundException {
        File file = new File(QUESTIONS_FILE);
        Scanner fileScanner = new Scanner(file);

        while (fileScanner.hasNextLine()) {
            String line = fileScanner.nextLine().trim();

            if (line.startsWith("Question:")) {
                String questionText = extractContent(line);
                String optionAText = extractContent(fileScanner.nextLine());
                String optionBText = extractContent(fileScanner.nextLine());
                String optionCText = extractContent(fileScanner.nextLine());
                String optionDText = extractContent(fileScanner.nextLine());
                String correctAnswer = extractContent(fileScanner.nextLine());

                Question question = new Question(questionText, optionAText, optionBText, optionCText, optionDText, correctAnswer);
                questions.add(question);
            }
        }
        fileScanner.close();
    }

    private String extractContent(String line) {
        int colonIndex = line.indexOf(":");
        if (colonIndex != -1) {
            return line.substring(colonIndex + 1).trim();
        } else {
            System.out.println("Invalid format in line: " + line);
            return "";
        }
    }

    public void startQuiz() {
        score = 0;

        System.out.println("\nWelcome to the Quiz Application!\n");

        for (int i = 0; i < questions.size(); i++) {
            Question question = questions.get(i);
            System.out.println("Question " + (i + 1) + ": " + question.getQuestionText());
            System.out.println("A: " + question.getOptionA());
            System.out.println("B: " + question.getOptionB());
            System.out.println("C: " + question.getOptionC());
            System.out.println("D: " + question.getOptionD());

            String userAnswer = getUserAnswer();

            if (question.isCorrectAnswer(userAnswer)) {
                System.out.println("Correct!\n");
                score += SCORE_PER_QUESTION;
            } else {
                System.out.println("Incorrect! The correct answer was: " + question.getCorrectAnswer() + "\n");
            }
        }

        System.out.println("Your final score is: " + score);
    }

    private String getUserAnswer() {
        System.out.print("Your Answer: ");
        return scanner.nextLine().toUpperCase();
    }

    public static void main(String[] args) {
        QuizApplication quiz = new QuizApplication();

        try {
            quiz.loadQuestions();
            quiz.startQuiz();
        } catch (FileNotFoundException e) {
            System.out.println("Failed to load questions from file: " + QUESTIONS_FILE);
        }
    }
}

