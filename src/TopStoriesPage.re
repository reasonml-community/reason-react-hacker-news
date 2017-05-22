module TopStoriesPage = {
  include ReactRe.Component.Stateful;
  type props = unit;
  type state = {topstories: StoryData.topstories, page: int};
  let name = "TopStoriesPage";
  let handleLoaded {state} (page, data) => {
    let updatedTopstories = Array.concat [state.topstories, data];
    Some {topstories: updatedTopstories, page: page + 1}
  };
  let getInitialState _ => {topstories: [||], page: 0};
  let componentDidMount {updater, state} => {
    StoryData.fetchTopStories state.page (updater handleLoaded);
    None
  };
  let componentDidUpdate prevProps::props prevState::state {updater, state} => {
    if (state.page < 4) {
      StoryData.fetchTopStories state.page (updater handleLoaded);
      ()
    };
    None
  };
  let render {state} => {
    let storyArray =
      if (Array.length state.topstories > 0) {
        Array.mapi
          (fun index story => <StoryListItem key=(string_of_int index) index story />)
          state.topstories
      } else {
        [||]
      };
    <div> (ReactRe.arrayToElement storyArray) </div>
  };
};

include ReactRe.CreateComponent TopStoriesPage;

let createElement = wrapProps ();
