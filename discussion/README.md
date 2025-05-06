# Discussion
- Questions and Answers
    - [View Questions CSV](../assets/SortingHat_Questions_and_Options.csv)

- Play with your sorting hat. Are all 10 questions important to create the sorting hat? If you were to remove some questions to improve user experience, which questions would you remove and justify your answer.

    - Not all 10 questions are equally impactful to create the sorting hat. During model testing, I observed that some questions introduced more noise than value.
    - I would like to remove (Q2. “What’s your favorite type of puzzle?”), because responses were often inconsistent and didn't clearly differentiate house traits. Also remove(Q5. “How do you prefer to spend free time?”). Because it overlaps with other personality-related questions (like Q8, Q9).

- If you were to improve the sorting hat, what technical improvements would you make? Consider:
  - How could you improve the model's accuracy or efficiency?
        **Increase the dataset size**
        The current dataset is simulated and relatively small. More data would allow the model to learn subtler patterns in how users respond.
    	**Model Pruning**
        Replace the basic Decision Tree with a pruned tree or a Random Forest (with very few trees) to reduce overfitting and improve generalization.
        **Feature Selection / Engineering**
        Instead of using all questions equally, I would analyze feature importance to keep only the most discriminative questions. This would reduce model complexity and make inference faster on ESP32.

  - What additional sensors or hardware could enhance the user experience?
        **RGB LEDs** – Show house colors visually
        **Buzzer/Speaker** – Add sound feedback or voice
        **Touch Sensors** – Replace physical buttons for smoother interaction
        **OLED Animation** – Display transitions or magical effects

  - Does decision tree remain suitable for your choice of new sensors? If yes, carefully justify your answer. If not, what ML model would you use and explain why.
    - Not always. A decision tree works well for simple button inputs. It’s fast and easy to run on ESP32. However, if we add new sensors, the input data becomes more complex. In that case, a decision tree may not be accurate enough.
    - Better alternative: TinyML model trained with TensorFlow Lite for Microcontrollers. It is optimized to run on devices like ESP32, can handle complex inputs, and still keeps memory usage low.